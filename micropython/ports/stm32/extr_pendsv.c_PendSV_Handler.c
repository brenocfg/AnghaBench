#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((naked)) void PendSV_Handler(void) {
    // Handle a PendSV interrupt
    //
    // For the case of an asynchronous exception, re-jig the
    // stack so that when we return from this interrupt handler
    // it returns instead to nlr_jump with argument pendsv_object
    // note that stack has a different layout if DEBUG is enabled
    //
    // For the case of a thread switch, swap stacks.
    //
    // on entry to this (naked) function, stack has the following layout:
    //
    // stack layout with DEBUG disabled:
    //   sp[6]: pc=r15
    //   sp[5]: lr=r14
    //   sp[4]: r12
    //   sp[3]: r3
    //   sp[2]: r2
    //   sp[1]: r1
    //   sp[0]: r0
    //
    // stack layout with DEBUG enabled:
    //   sp[8]: pc=r15
    //   sp[7]: lr=r14
    //   sp[6]: r12
    //   sp[5]: r3
    //   sp[4]: r2
    //   sp[3]: r1
    //   sp[2]: r0
    //   sp[1]: 0xfffffff9
    //   sp[0]: ?

    __asm volatile (
        #if defined(PENDSV_DISPATCH_NUM_SLOTS)
        // Check if there are any pending calls to dispatch to
        "ldr r1, pendsv_dispatch_active_ptr\n"
        "ldr r0, [r1]\n"
        "cmp r0, #0\n"
        "beq .no_dispatch\n"
        "mov r2, #0\n"
        "str r2, [r1]\n"                // clear pendsv_dispatch_active
        "b pendsv_dispatch_handler\n"   // jump to the handler
        ".no_dispatch:\n"
        #endif

        // Check if there is an active object to throw via nlr_jump
        "ldr r1, pendsv_object_ptr\n"
        "ldr r0, [r1]\n"
        "cmp r0, #0\n"
        "beq .no_obj\n"
        #if defined(PENDSV_DEBUG)
        "str r0, [sp, #8]\n"            // store to r0 on stack
        #else
        "str r0, [sp, #0]\n"            // store to r0 on stack
        #endif
        "mov r0, #0\n"
        "str r0, [r1]\n"                // clear pendsv_object
        "ldr r0, nlr_jump_ptr\n"
        #if defined(PENDSV_DEBUG)
        "str r0, [sp, #32]\n"           // store to pc on stack
        #else
        "str r0, [sp, #24]\n"           // store to pc on stack
        #endif
        "bx lr\n"                       // return from interrupt; will return to nlr_jump
        ".no_obj:\n"                    // pendsv_object==NULL

        #if MICROPY_PY_THREAD
        // Do a thread context switch
        "push {r4-r11, lr}\n"
        "vpush {s16-s31}\n"
        "mrs r5, primask\n"             // save PRIMASK in r5
        "cpsid i\n"                     // disable interrupts while we change stacks
        "mov r0, sp\n"                  // pass sp to save
        "mov r4, lr\n"                  // save lr because we are making a call
        "bl pyb_thread_next\n"          // get next thread to execute
        "mov lr, r4\n"                  // restore lr
        "mov sp, r0\n"                  // switch stacks
        "msr primask, r5\n"             // reenable interrupts
        "vpop {s16-s31}\n"
        "pop {r4-r11, lr}\n"
        "bx lr\n"                       // return from interrupt; will return to new thread
        #else
        // Spurious pendsv, just return
        "bx lr\n"
        #endif

        // Data
        ".align 2\n"
        #if defined(PENDSV_DISPATCH_NUM_SLOTS)
        "pendsv_dispatch_active_ptr: .word pendsv_dispatch_active\n"
        #endif
        "pendsv_object_ptr: .word pendsv_object\n"
        "nlr_jump_ptr: .word nlr_jump\n"
    );
}
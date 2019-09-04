#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  xpsr; int /*<<< orphan*/  pc; int /*<<< orphan*/  lr; int /*<<< orphan*/  r12; int /*<<< orphan*/  r3; int /*<<< orphan*/  r2; int /*<<< orphan*/  r1; int /*<<< orphan*/  r0; } ;
typedef  TYPE_1__ ExceptionRegisters_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 int /*<<< orphan*/  __fatal_error (char*) ; 
 int /*<<< orphan*/  _estack ; 
 int /*<<< orphan*/  _heap_end ; 
 int /*<<< orphan*/  _ram_end ; 
 int /*<<< orphan*/  _ram_start ; 
 int /*<<< orphan*/  mp_hal_stdout_tx_str (char*) ; 
 int /*<<< orphan*/  print_hex_hex (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_reg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_hard_fault_debug ; 

void HardFault_C_Handler(ExceptionRegisters_t *regs) {
    if (!pyb_hard_fault_debug) {
        NVIC_SystemReset();
    }

    #if MICROPY_HW_ENABLE_USB
    // We need to disable the USB so it doesn't try to write data out on
    // the VCP and then block indefinitely waiting for the buffer to drain.
    pyb_usb_flags = 0;
    #endif

    mp_hal_stdout_tx_str("HardFault\r\n");

    print_reg("R0    ", regs->r0);
    print_reg("R1    ", regs->r1);
    print_reg("R2    ", regs->r2);
    print_reg("R3    ", regs->r3);
    print_reg("R12   ", regs->r12);
    print_reg("SP    ", (uint32_t)regs);
    print_reg("LR    ", regs->lr);
    print_reg("PC    ", regs->pc);
    print_reg("XPSR  ", regs->xpsr);

    #if __CORTEX_M >= 3
    uint32_t cfsr = SCB->CFSR;

    print_reg("HFSR  ", SCB->HFSR);
    print_reg("CFSR  ", cfsr);
    if (cfsr & 0x80) {
        print_reg("MMFAR ", SCB->MMFAR);
    }
    if (cfsr & 0x8000) {
        print_reg("BFAR  ", SCB->BFAR);
    }
    #endif

    if ((void*)&_ram_start <= (void*)regs && (void*)regs < (void*)&_ram_end) {
        mp_hal_stdout_tx_str("Stack:\r\n");
        uint32_t *stack_top = &_estack;
        if ((void*)regs < (void*)&_heap_end) {
            // stack not in static stack area so limit the amount we print
            stack_top = (uint32_t*)regs + 32;
        }
        for (uint32_t *sp = (uint32_t*)regs; sp < stack_top; ++sp) {
            print_hex_hex("  ", (uint32_t)sp, *sp);
        }
    }

    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
        __fatal_error("HardFault");
    }
}
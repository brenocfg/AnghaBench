#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct coro {unsigned char* stack; uintptr_t* context; int /*<<< orphan*/  defer; } ;
typedef  scalar_t__ coro_function_t ;
struct TYPE_2__ {unsigned char* ss_sp; uintptr_t ss_size; scalar_t__ ss_flags; } ;

/* Variables and functions */
 uintptr_t CORO_STACK_MIN ; 
 size_t STACK_PTR ; 
 int /*<<< orphan*/  coro_defer_array_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coro_deferred_run (struct coro*,int /*<<< orphan*/ ) ; 
 scalar_t__ coro_entry_point ; 
 int /*<<< orphan*/  getcontext (uintptr_t**) ; 
 int /*<<< orphan*/  makecontext (uintptr_t**,void (*) (),int,struct coro*,scalar_t__,void*) ; 

void coro_reset(struct coro *coro, coro_function_t func, void *data)
{
    unsigned char *stack = coro->stack;

    coro_deferred_run(coro, 0);
    coro_defer_array_reset(&coro->defer);

#if defined(__x86_64__)
    /* coro_entry_point() for x86-64 has 3 arguments, but RDX isn't
     * stored.  Use R15 instead, and implement the trampoline
     * function in assembly in order to use this register when
     * calling the user function. */
    coro->context[5 /* R15 */] = (uintptr_t)data;
    coro->context[6 /* RDI */] = (uintptr_t)coro;
    coro->context[7 /* RSI */] = (uintptr_t)func;
    coro->context[8 /* RIP */] = (uintptr_t)coro_entry_point;

    /* Ensure stack is properly aligned: it should be aligned to a
     * 16-bytes boundary so SSE will work properly, but should be
     * aligned on an 8-byte boundary right after calling a function. */
    uintptr_t rsp = (uintptr_t)stack + CORO_STACK_MIN;

#define STACK_PTR 9
    coro->context[STACK_PTR] = (rsp & ~0xful) - 0x8ul;
#elif defined(__i386__)
    stack = (unsigned char *)(uintptr_t)(stack + CORO_STACK_MIN);

    /* Make room for 3 args */
    stack -= sizeof(uintptr_t) * 3;
    /* Ensure 4-byte alignment */
    stack = (unsigned char *)((uintptr_t)stack & (uintptr_t)~0x3);

    uintptr_t *argp = (uintptr_t *)stack;
    *argp++ = 0;
    *argp++ = (uintptr_t)coro;
    *argp++ = (uintptr_t)func;
    *argp++ = (uintptr_t)data;

    coro->context[5 /* EIP */] = (uintptr_t)coro_entry_point;

#define STACK_PTR 6
    coro->context[STACK_PTR] = (uintptr_t)stack;
#else
    getcontext(&coro->context);

    coro->context.uc_stack.ss_sp = stack;
    coro->context.uc_stack.ss_size = CORO_STACK_MIN;
    coro->context.uc_stack.ss_flags = 0;
    coro->context.uc_link = NULL;

    makecontext(&coro->context, (void (*)())coro_entry_point, 3, coro, func,
                data);
#endif
}
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

void
mch_early_init()
{
#ifdef HAVE_CHECK_STACK_GROWTH
    int			i;

    check_stack_growth((char *)&i);

# ifdef HAVE_STACK_LIMIT
    get_stack_limit();
# endif

#endif

    /*
     * Setup an alternative stack for signals.  Helps to catch signals when
     * running out of stack space.
     * Use of sigaltstack() is preferred, it's more portable.
     * Ignore any errors.
     */
#if defined(HAVE_SIGALTSTACK) || defined(HAVE_SIGSTACK)
    signal_stack = (char *)alloc(SIGSTKSZ);
    init_signal_stack();
#endif

#ifdef FEAT_GUI_MACVIM
    macvim_early_init();
#endif
}
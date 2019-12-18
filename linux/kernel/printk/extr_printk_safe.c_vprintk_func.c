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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  LOGLEVEL_DEFAULT ; 
 int PRINTK_NMI_CONTEXT_MASK ; 
 int PRINTK_NMI_DIRECT_CONTEXT_MASK ; 
 int PRINTK_SAFE_CONTEXT_MASK ; 
 int /*<<< orphan*/  defer_console_output () ; 
 int /*<<< orphan*/  logbuf_lock ; 
 int /*<<< orphan*/  printk_context ; 
 scalar_t__ raw_spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int vprintk_default (char const*,int /*<<< orphan*/ ) ; 
 int vprintk_nmi (char const*,int /*<<< orphan*/ ) ; 
 int vprintk_safe (char const*,int /*<<< orphan*/ ) ; 
 int vprintk_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int vprintk_func(const char *fmt, va_list args)
{
	/*
	 * Try to use the main logbuf even in NMI. But avoid calling console
	 * drivers that might have their own locks.
	 */
	if ((this_cpu_read(printk_context) & PRINTK_NMI_DIRECT_CONTEXT_MASK) &&
	    raw_spin_trylock(&logbuf_lock)) {
		int len;

		len = vprintk_store(0, LOGLEVEL_DEFAULT, NULL, 0, fmt, args);
		raw_spin_unlock(&logbuf_lock);
		defer_console_output();
		return len;
	}

	/* Use extra buffer in NMI when logbuf_lock is taken or in safe mode. */
	if (this_cpu_read(printk_context) & PRINTK_NMI_CONTEXT_MASK)
		return vprintk_nmi(fmt, args);

	/* Use extra buffer to prevent a recursion deadlock in safe mode. */
	if (this_cpu_read(printk_context) & PRINTK_SAFE_CONTEXT_MASK)
		return vprintk_safe(fmt, args);

	/* No obstacles. */
	return vprintk_default(fmt, args);
}
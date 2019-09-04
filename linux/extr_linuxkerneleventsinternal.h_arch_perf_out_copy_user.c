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
 unsigned long __copy_from_user_inatomic (void*,void const*,unsigned long) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 

__attribute__((used)) static inline unsigned long
arch_perf_out_copy_user(void *dst, const void *src, unsigned long n)
{
	unsigned long ret;

	pagefault_disable();
	ret = __copy_from_user_inatomic(dst, src, n);
	pagefault_enable();

	return ret;
}
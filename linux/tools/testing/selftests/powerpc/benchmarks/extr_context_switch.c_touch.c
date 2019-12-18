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
 scalar_t__ a ; 
 int /*<<< orphan*/  altivec_touch_fn () ; 
 scalar_t__ b ; 
 scalar_t__ c ; 
 double fp ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ touch_altivec ; 
 scalar_t__ touch_fp ; 
 scalar_t__ touch_vdso ; 
 scalar_t__ touch_vector ; 
 int /*<<< orphan*/  tv ; 

__attribute__((used)) static void touch(void)
{
	if (touch_vdso)
		gettimeofday(&tv, NULL);

	if (touch_fp)
		fp += 0.1;

#ifdef __powerpc__
	if (touch_altivec)
		altivec_touch_fn();
#endif

	if (touch_vector)
		c = a + b;

	asm volatile("# %0 %1 %2": : "r"(&tv), "r"(&fp), "r"(&c));
}
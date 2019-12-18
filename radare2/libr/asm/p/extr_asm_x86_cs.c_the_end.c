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
 scalar_t__ cd ; 
 int /*<<< orphan*/  cs_close (scalar_t__*) ; 
 int /*<<< orphan*/  cs_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * insn ; 
 int /*<<< orphan*/  n ; 

__attribute__((used)) static bool the_end(void *p) {
#if 0
#if !USE_ITER_API
	if (insn) {
		cs_free (insn, n);
		insn = NULL;
	}
#endif
#endif
	if (cd) {
		cs_close (&cd);
		cd = 0;
	}
	return true;
}
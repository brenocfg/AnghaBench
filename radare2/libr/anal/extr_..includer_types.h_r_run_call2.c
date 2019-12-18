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
 void stub1 (void*,void*) ; 

__attribute__((used)) static inline void r_run_call2(void *fcn, void *arg1, void *arg2) {
	((void (*)(void *, void *))(fcn))(arg1, arg2);
}
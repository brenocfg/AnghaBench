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
typedef  int /*<<< orphan*/  RAnalVTable ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_class_vtable_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_anal_class_vtable_fini_proxy(void *e, void *user) {
	(void)user;
	RAnalVTable *vtable = e;
	r_anal_class_vtable_fini (vtable);
}
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
struct clone_root {TYPE_1__* root; } ;
struct TYPE_2__ {scalar_t__ objectid; } ;

/* Variables and functions */

__attribute__((used)) static int __clone_root_cmp_sort(const void *e1, const void *e2)
{
	struct clone_root *cr1 = (struct clone_root *)e1;
	struct clone_root *cr2 = (struct clone_root *)e2;

	if (cr1->root->objectid < cr2->root->objectid)
		return -1;
	if (cr1->root->objectid > cr2->root->objectid)
		return 1;
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clone_root {TYPE_2__* root; } ;
struct TYPE_3__ {scalar_t__ objectid; } ;
struct TYPE_4__ {TYPE_1__ root_key; } ;

/* Variables and functions */

__attribute__((used)) static int __clone_root_cmp_sort(const void *e1, const void *e2)
{
	struct clone_root *cr1 = (struct clone_root *)e1;
	struct clone_root *cr2 = (struct clone_root *)e2;

	if (cr1->root->root_key.objectid < cr2->root->root_key.objectid)
		return -1;
	if (cr1->root->root_key.objectid > cr2->root->root_key.objectid)
		return 1;
	return 0;
}
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
typedef  scalar_t__ u64 ;
struct clone_root {TYPE_1__* root; } ;
struct TYPE_2__ {scalar_t__ objectid; } ;

/* Variables and functions */

__attribute__((used)) static int __clone_root_cmp_bsearch(const void *key, const void *elt)
{
	u64 root = (u64)(uintptr_t)key;
	struct clone_root *cr = (struct clone_root *)elt;

	if (root < cr->root->objectid)
		return -1;
	if (root > cr->root->objectid)
		return 1;
	return 0;
}
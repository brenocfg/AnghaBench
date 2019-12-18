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
typedef  scalar_t__ u64 ;
struct clone_root {TYPE_2__* root; } ;
struct TYPE_3__ {scalar_t__ objectid; } ;
struct TYPE_4__ {TYPE_1__ root_key; } ;

/* Variables and functions */

__attribute__((used)) static int __clone_root_cmp_bsearch(const void *key, const void *elt)
{
	u64 root = (u64)(uintptr_t)key;
	struct clone_root *cr = (struct clone_root *)elt;

	if (root < cr->root->root_key.objectid)
		return -1;
	if (root > cr->root->root_key.objectid)
		return 1;
	return 0;
}
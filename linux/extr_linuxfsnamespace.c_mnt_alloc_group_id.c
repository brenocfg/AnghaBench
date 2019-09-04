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
struct mount {int mnt_group_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_alloc_min (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_group_ida ; 

__attribute__((used)) static int mnt_alloc_group_id(struct mount *mnt)
{
	int res = ida_alloc_min(&mnt_group_ida, 1, GFP_KERNEL);

	if (res < 0)
		return res;
	mnt->mnt_group_id = res;
	return 0;
}
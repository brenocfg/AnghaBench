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
struct mount {int mnt_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_id_ida ; 

__attribute__((used)) static int mnt_alloc_id(struct mount *mnt)
{
	int res = ida_alloc(&mnt_id_ida, GFP_KERNEL);

	if (res < 0)
		return res;
	mnt->mnt_id = res;
	return 0;
}
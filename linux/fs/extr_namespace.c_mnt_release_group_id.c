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
struct mount {scalar_t__ mnt_group_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mnt_group_ida ; 

void mnt_release_group_id(struct mount *mnt)
{
	ida_free(&mnt_group_ida, mnt->mnt_group_id);
	mnt->mnt_group_id = 0;
}
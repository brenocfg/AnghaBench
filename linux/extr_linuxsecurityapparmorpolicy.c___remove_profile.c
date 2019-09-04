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
struct TYPE_4__ {int /*<<< orphan*/  profiles; } ;
struct aa_profile {int /*<<< orphan*/  label; TYPE_2__ base; TYPE_1__* ns; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  __aa_profile_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __aafs_profile_rmdir (struct aa_profile*) ; 
 int /*<<< orphan*/  __list_remove_profile (struct aa_profile*) ; 
 int /*<<< orphan*/  aa_label_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __remove_profile(struct aa_profile *profile)
{
	AA_BUG(!profile);
	AA_BUG(!profile->ns);
	AA_BUG(!mutex_is_locked(&profile->ns->lock));

	/* release any children lists first */
	__aa_profile_list_release(&profile->base.profiles);
	/* released by free_profile */
	aa_label_remove(&profile->label);
	__aafs_profile_rmdir(profile);
	__list_remove_profile(profile);
}
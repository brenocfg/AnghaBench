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
struct kobject {TYPE_1__* ktype; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_ownership ) (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  stub1 (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void kobject_get_ownership(struct kobject *kobj, kuid_t *uid, kgid_t *gid)
{
	*uid = GLOBAL_ROOT_UID;
	*gid = GLOBAL_ROOT_GID;

	if (kobj->ktype->get_ownership)
		kobj->ktype->get_ownership(kobj, uid, gid);
}
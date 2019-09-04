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
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 int /*<<< orphan*/  kobject_del (struct kobject*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  kobject_uevent (struct kobject*,int /*<<< orphan*/ ) ; 

void batadv_sysfs_del_hardif(struct kobject **hardif_obj)
{
	kobject_uevent(*hardif_obj, KOBJ_REMOVE);
	kobject_del(*hardif_obj);
	kobject_put(*hardif_obj);
	*hardif_obj = NULL;
}
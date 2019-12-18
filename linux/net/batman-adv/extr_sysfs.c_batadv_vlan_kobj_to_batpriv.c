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
struct kobject {struct kobject* parent; int /*<<< orphan*/  name; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_SYSFS_IF_MESH_SUBDIR ; 
 struct batadv_priv* batadv_kobj_to_batpriv (struct kobject*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct batadv_priv *batadv_vlan_kobj_to_batpriv(struct kobject *obj)
{
	/* VLAN specific attributes are located in the root sysfs folder if they
	 * refer to the untagged VLAN..
	 */
	if (!strcmp(BATADV_SYSFS_IF_MESH_SUBDIR, obj->name))
		return batadv_kobj_to_batpriv(obj);

	/* ..while the attributes for the tagged vlans are located in
	 * the in the corresponding "vlan%VID" subfolder
	 */
	return batadv_kobj_to_batpriv(obj->parent);
}
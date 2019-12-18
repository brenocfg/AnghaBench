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
typedef  int u32 ;
struct kobject {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bandwidth_up; int /*<<< orphan*/  bandwidth_down; } ;
struct batadv_priv {TYPE_1__ gw; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct batadv_priv* batadv_kobj_to_batpriv (struct kobject*) ; 
 int /*<<< orphan*/  batadv_sysfs_deprecated (struct attribute*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 

__attribute__((used)) static ssize_t batadv_show_gw_bwidth(struct kobject *kobj,
				     struct attribute *attr, char *buff)
{
	struct batadv_priv *bat_priv = batadv_kobj_to_batpriv(kobj);
	u32 down, up;

	batadv_sysfs_deprecated(attr);

	down = atomic_read(&bat_priv->gw.bandwidth_down);
	up = atomic_read(&bat_priv->gw.bandwidth_up);

	return sprintf(buff, "%u.%u/%u.%u MBit\n", down / 10,
		       down % 10, up / 10, up % 10);
}
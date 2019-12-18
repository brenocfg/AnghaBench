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
struct switch_dev {int dummy; } ;
struct adm6996_priv {int* pvid; } ;

/* Variables and functions */
 int ADM_VLAN_MAX_ID ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_devel (char*,int,int) ; 
 struct adm6996_priv* to_adm (struct switch_dev*) ; 

__attribute__((used)) static int
adm6996_set_pvid(struct switch_dev *dev, int port, int vlan)
{
	struct adm6996_priv *priv = to_adm(dev);

	pr_devel("set_pvid port %d vlan %d\n", port, vlan);

	if (vlan > ADM_VLAN_MAX_ID)
		return -EINVAL;

	priv->pvid[port] = vlan;

	return 0;
}
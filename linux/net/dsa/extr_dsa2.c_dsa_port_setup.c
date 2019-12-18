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
struct dsa_switch_tree {int /*<<< orphan*/  index; } ;
struct dsa_switch {struct devlink* devlink; struct dsa_switch_tree* dst; } ;
struct devlink_port {int dummy; } ;
struct dsa_port {int type; int /*<<< orphan*/  slave; int /*<<< orphan*/  dn; int /*<<< orphan*/  mac; int /*<<< orphan*/  index; struct devlink_port devlink_port; struct dsa_switch* ds; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_CPU ; 
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_DSA ; 
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_PHYSICAL ; 
#define  DSA_PORT_TYPE_CPU 131 
#define  DSA_PORT_TYPE_DSA 130 
#define  DSA_PORT_TYPE_UNUSED 129 
#define  DSA_PORT_TYPE_USER 128 
 int /*<<< orphan*/  devlink_port_attrs_set (struct devlink_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char const*,unsigned char const) ; 
 int devlink_port_register (struct devlink*,struct devlink_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_type_eth_set (struct devlink_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_unregister (struct devlink_port*) ; 
 int /*<<< orphan*/  dsa_port_disable (struct dsa_port*) ; 
 int dsa_port_enable (struct dsa_port*,int /*<<< orphan*/ *) ; 
 int dsa_port_link_register_of (struct dsa_port*) ; 
 int /*<<< orphan*/  dsa_port_link_unregister_of (struct dsa_port*) ; 
 int dsa_slave_create (struct dsa_port*) ; 
 int /*<<< orphan*/  memset (struct devlink_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_get_mac_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_port_setup(struct dsa_port *dp)
{
	struct dsa_switch *ds = dp->ds;
	struct dsa_switch_tree *dst = ds->dst;
	const unsigned char *id = (const unsigned char *)&dst->index;
	const unsigned char len = sizeof(dst->index);
	struct devlink_port *dlp = &dp->devlink_port;
	bool dsa_port_link_registered = false;
	bool devlink_port_registered = false;
	struct devlink *dl = ds->devlink;
	bool dsa_port_enabled = false;
	int err = 0;

	switch (dp->type) {
	case DSA_PORT_TYPE_UNUSED:
		dsa_port_disable(dp);
		break;
	case DSA_PORT_TYPE_CPU:
		memset(dlp, 0, sizeof(*dlp));
		devlink_port_attrs_set(dlp, DEVLINK_PORT_FLAVOUR_CPU,
				       dp->index, false, 0, id, len);
		err = devlink_port_register(dl, dlp, dp->index);
		if (err)
			break;
		devlink_port_registered = true;

		err = dsa_port_link_register_of(dp);
		if (err)
			break;
		dsa_port_link_registered = true;

		err = dsa_port_enable(dp, NULL);
		if (err)
			break;
		dsa_port_enabled = true;

		break;
	case DSA_PORT_TYPE_DSA:
		memset(dlp, 0, sizeof(*dlp));
		devlink_port_attrs_set(dlp, DEVLINK_PORT_FLAVOUR_DSA,
				       dp->index, false, 0, id, len);
		err = devlink_port_register(dl, dlp, dp->index);
		if (err)
			break;
		devlink_port_registered = true;

		err = dsa_port_link_register_of(dp);
		if (err)
			break;
		dsa_port_link_registered = true;

		err = dsa_port_enable(dp, NULL);
		if (err)
			break;
		dsa_port_enabled = true;

		break;
	case DSA_PORT_TYPE_USER:
		memset(dlp, 0, sizeof(*dlp));
		devlink_port_attrs_set(dlp, DEVLINK_PORT_FLAVOUR_PHYSICAL,
				       dp->index, false, 0, id, len);
		err = devlink_port_register(dl, dlp, dp->index);
		if (err)
			break;
		devlink_port_registered = true;

		dp->mac = of_get_mac_address(dp->dn);
		err = dsa_slave_create(dp);
		if (err)
			break;

		devlink_port_type_eth_set(dlp, dp->slave);
		break;
	}

	if (err && dsa_port_enabled)
		dsa_port_disable(dp);
	if (err && dsa_port_link_registered)
		dsa_port_link_unregister_of(dp);
	if (err && devlink_port_registered)
		devlink_port_unregister(dlp);

	return err;
}
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
struct mwifiex_private {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */

int mwifiex_dnld_dt_cfgdata(struct mwifiex_private *priv,
			    struct device_node *node, const char *prefix)
{
#ifdef CONFIG_OF
	struct property *prop;
	size_t len = strlen(prefix);
	int ret;

	/* look for all matching property names */
	for_each_property_of_node(node, prop) {
		if (len > strlen(prop->name) ||
		    strncmp(prop->name, prefix, len))
			continue;

		/* property header is 6 bytes, data must fit in cmd buffer */
		if (prop->value && prop->length > 6 &&
		    prop->length <= MWIFIEX_SIZE_OF_CMD_BUFFER - S_DS_GEN) {
			ret = mwifiex_send_cmd(priv, HostCmd_CMD_CFG_DATA,
					       HostCmd_ACT_GEN_SET, 0,
					       prop, true);
			if (ret)
				return ret;
		}
	}
#endif
	return 0;
}
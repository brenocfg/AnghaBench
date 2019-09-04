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
typedef  int /*<<< orphan*/  u32 ;
struct wl1251 {int dummy; } ;
struct acx_feature_config {scalar_t__ options; int /*<<< orphan*/  data_flow_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_FEATURE_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_feature_config*) ; 
 struct acx_feature_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_feature_config*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 

int wl1251_acx_feature_cfg(struct wl1251 *wl, u32 data_flow_options)
{
	struct acx_feature_config *feature;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx feature cfg");

	feature = kzalloc(sizeof(*feature), GFP_KERNEL);
	if (!feature)
		return -ENOMEM;

	/* DF_ENCRYPTION_DISABLE and DF_SNIFF_MODE_ENABLE can be set */
	feature->data_flow_options = data_flow_options;
	feature->options = 0;

	ret = wl1251_cmd_configure(wl, ACX_FEATURE_CFG,
				   feature, sizeof(*feature));
	if (ret < 0) {
		wl1251_error("Couldn't set HW encryption");
		goto out;
	}

out:
	kfree(feature);
	return ret;
}
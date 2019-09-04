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
struct wcn36xx {int /*<<< orphan*/  fw_feat_caps; } ;

/* Variables and functions */
 int MAX_FEATURE_SUPPORTED ; 
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 scalar_t__ get_feat_caps (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_get_cap_name (int) ; 

__attribute__((used)) static void wcn36xx_feat_caps_info(struct wcn36xx *wcn)
{
	int i;

	for (i = 0; i < MAX_FEATURE_SUPPORTED; i++) {
		if (get_feat_caps(wcn->fw_feat_caps, i))
			wcn36xx_dbg(WCN36XX_DBG_MAC, "FW Cap %s\n", wcn36xx_get_cap_name(i));
	}
}
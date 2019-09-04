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
struct TYPE_3__ {int /*<<< orphan*/  rssi; } ;
struct mwifiex_sta_node {TYPE_1__ stats; } ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_ie_types_sta_info {int /*<<< orphan*/  rssi; int /*<<< orphan*/  mac; } ;
struct host_cmd_ds_sta_list {int /*<<< orphan*/  sta_count; int /*<<< orphan*/  tlv; } ;
struct TYPE_4__ {struct host_cmd_ds_sta_list sta_list; } ;
struct host_cmd_ds_command {TYPE_2__ params; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mwifiex_ret_uap_sta_list(struct mwifiex_private *priv,
				    struct host_cmd_ds_command *resp)
{
	struct host_cmd_ds_sta_list *sta_list =
		&resp->params.sta_list;
	struct mwifiex_ie_types_sta_info *sta_info = (void *)&sta_list->tlv;
	int i;
	struct mwifiex_sta_node *sta_node;

	for (i = 0; i < (le16_to_cpu(sta_list->sta_count)); i++) {
		sta_node = mwifiex_get_sta_entry(priv, sta_info->mac);
		if (unlikely(!sta_node))
			continue;

		sta_node->stats.rssi = sta_info->rssi;
		sta_info++;
	}

	return 0;
}
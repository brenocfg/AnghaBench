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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct mwifiex_ietypes_domain_param_set {TYPE_1__ header; } ;
struct ieee80211_country_ie_triplet {int dummy; } ;
struct host_cmd_ds_802_11d_domain_info_rsp {scalar_t__ action; struct mwifiex_ietypes_domain_param_set domain; } ;
struct TYPE_4__ {struct host_cmd_ds_802_11d_domain_info_rsp domain_info_resp; } ;
struct host_cmd_ds_command {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
#define  HostCmd_ACT_GEN_GET 129 
#define  HostCmd_ACT_GEN_SET 128 
 int IEEE80211_COUNTRY_STRING_LEN ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ MWIFIEX_MAX_TRIPLET_802_11D ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int mwifiex_ret_802_11d_domain_info(struct mwifiex_private *priv,
					   struct host_cmd_ds_command *resp)
{
	struct host_cmd_ds_802_11d_domain_info_rsp *domain_info =
		&resp->params.domain_info_resp;
	struct mwifiex_ietypes_domain_param_set *domain = &domain_info->domain;
	u16 action = le16_to_cpu(domain_info->action);
	u8 no_of_triplet;

	no_of_triplet = (u8) ((le16_to_cpu(domain->header.len)
				- IEEE80211_COUNTRY_STRING_LEN)
			      / sizeof(struct ieee80211_country_ie_triplet));

	mwifiex_dbg(priv->adapter, INFO,
		    "info: 11D Domain Info Resp: no_of_triplet=%d\n",
		    no_of_triplet);

	if (no_of_triplet > MWIFIEX_MAX_TRIPLET_802_11D) {
		mwifiex_dbg(priv->adapter, FATAL,
			    "11D: invalid number of triplets %d returned\n",
			    no_of_triplet);
		return -1;
	}

	switch (action) {
	case HostCmd_ACT_GEN_SET:  /* Proc Set Action */
		break;
	case HostCmd_ACT_GEN_GET:
		break;
	default:
		mwifiex_dbg(priv->adapter, ERROR,
			    "11D: invalid action:%d\n", domain_info->action);
		return -1;
	}

	return 0;
}
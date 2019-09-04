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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct network_info {int ssid_len; scalar_t__ ies_len; int /*<<< orphan*/  tsf_lo; int /*<<< orphan*/  ies; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; int /*<<< orphan*/  cap_info; int /*<<< orphan*/  beacon_period; int /*<<< orphan*/  dtim_period; } ;
struct join_bss_param {int ssid_len; int /*<<< orphan*/  rsn_auth_policy; int /*<<< orphan*/  rsn_pcip_policy; scalar_t__ ssid; int /*<<< orphan*/ * bssid; int /*<<< orphan*/  cap_info; int /*<<< orphan*/  beacon_period; int /*<<< orphan*/  dtim_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  host_int_fill_join_bss_param (struct join_bss_param*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct join_bss_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void *host_int_parse_join_bss_param(struct network_info *info)
{
	struct join_bss_param *param;
	u16 index = 0;
	u8 rates_no = 0;
	u8 pcipher_total_cnt = 0;
	u8 auth_total_cnt = 0;

	param = kzalloc(sizeof(*param), GFP_KERNEL);
	if (!param)
		return NULL;

	param->dtim_period = info->dtim_period;
	param->beacon_period = info->beacon_period;
	param->cap_info = info->cap_info;
	memcpy(param->bssid, info->bssid, 6);
	memcpy((u8 *)param->ssid, info->ssid, info->ssid_len + 1);
	param->ssid_len = info->ssid_len;
	memset(param->rsn_pcip_policy, 0xFF, 3);
	memset(param->rsn_auth_policy, 0xFF, 3);

	while (index < info->ies_len)
		host_int_fill_join_bss_param(param, info->ies, &index,
					     &pcipher_total_cnt,
					     &auth_total_cnt, info->tsf_lo,
					     &rates_no);

	return (void *)param;
}
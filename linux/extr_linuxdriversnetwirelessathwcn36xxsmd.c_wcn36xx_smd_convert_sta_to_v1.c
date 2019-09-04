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
struct wcn36xx_hal_config_sta_params_v1 {int /*<<< orphan*/  p2p; int /*<<< orphan*/  bssid_index; int /*<<< orphan*/  sta_index; int /*<<< orphan*/  supported_rates; int /*<<< orphan*/  dsss_cck_mode_40mhz; int /*<<< orphan*/  max_ampdu_duration; int /*<<< orphan*/  delayed_ba_support; int /*<<< orphan*/  mimo_ps; int /*<<< orphan*/  green_field_capable; int /*<<< orphan*/  max_sp_len; int /*<<< orphan*/  uapsd; int /*<<< orphan*/  action; int /*<<< orphan*/  encrypt_type; int /*<<< orphan*/  rmf; int /*<<< orphan*/  sgi_20Mhz; int /*<<< orphan*/  sgi_40mhz; int /*<<< orphan*/  max_ampdu_density; int /*<<< orphan*/  max_ampdu_size; int /*<<< orphan*/  lsig_txop_protection; int /*<<< orphan*/  rifs_mode; int /*<<< orphan*/  tx_channel_width_set; int /*<<< orphan*/  ht_capable; int /*<<< orphan*/  wmm_enabled; int /*<<< orphan*/  listen_interval; int /*<<< orphan*/  short_preamble_supported; int /*<<< orphan*/  type; int /*<<< orphan*/  aid; int /*<<< orphan*/  mac; int /*<<< orphan*/  bssid; } ;
struct wcn36xx_hal_config_sta_params {int /*<<< orphan*/  p2p; int /*<<< orphan*/  bssid_index; int /*<<< orphan*/  sta_index; int /*<<< orphan*/  supported_rates; int /*<<< orphan*/  dsss_cck_mode_40mhz; int /*<<< orphan*/  max_ampdu_duration; int /*<<< orphan*/  delayed_ba_support; int /*<<< orphan*/  mimo_ps; int /*<<< orphan*/  green_field_capable; int /*<<< orphan*/  max_sp_len; int /*<<< orphan*/  uapsd; int /*<<< orphan*/  action; int /*<<< orphan*/  encrypt_type; int /*<<< orphan*/  rmf; int /*<<< orphan*/  sgi_20Mhz; int /*<<< orphan*/  sgi_40mhz; int /*<<< orphan*/  max_ampdu_density; int /*<<< orphan*/  max_ampdu_size; int /*<<< orphan*/  lsig_txop_protection; int /*<<< orphan*/  rifs_mode; int /*<<< orphan*/  tx_channel_width_set; int /*<<< orphan*/  ht_capable; int /*<<< orphan*/  wmm_enabled; int /*<<< orphan*/  listen_interval; int /*<<< orphan*/  short_preamble_supported; int /*<<< orphan*/  type; int /*<<< orphan*/  aid; int /*<<< orphan*/ * mac; int /*<<< orphan*/ * bssid; } ;
struct wcn36xx {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void wcn36xx_smd_convert_sta_to_v1(struct wcn36xx *wcn,
			const struct wcn36xx_hal_config_sta_params *orig,
			struct wcn36xx_hal_config_sta_params_v1 *v1)
{
	/* convert orig to v1 format */
	memcpy(&v1->bssid, orig->bssid, ETH_ALEN);
	memcpy(&v1->mac, orig->mac, ETH_ALEN);
	v1->aid = orig->aid;
	v1->type = orig->type;
	v1->short_preamble_supported = orig->short_preamble_supported;
	v1->listen_interval = orig->listen_interval;
	v1->wmm_enabled = orig->wmm_enabled;
	v1->ht_capable = orig->ht_capable;
	v1->tx_channel_width_set = orig->tx_channel_width_set;
	v1->rifs_mode = orig->rifs_mode;
	v1->lsig_txop_protection = orig->lsig_txop_protection;
	v1->max_ampdu_size = orig->max_ampdu_size;
	v1->max_ampdu_density = orig->max_ampdu_density;
	v1->sgi_40mhz = orig->sgi_40mhz;
	v1->sgi_20Mhz = orig->sgi_20Mhz;
	v1->rmf = orig->rmf;
	v1->encrypt_type = orig->encrypt_type;
	v1->action = orig->action;
	v1->uapsd = orig->uapsd;
	v1->max_sp_len = orig->max_sp_len;
	v1->green_field_capable = orig->green_field_capable;
	v1->mimo_ps = orig->mimo_ps;
	v1->delayed_ba_support = orig->delayed_ba_support;
	v1->max_ampdu_duration = orig->max_ampdu_duration;
	v1->dsss_cck_mode_40mhz = orig->dsss_cck_mode_40mhz;
	memcpy(&v1->supported_rates, &orig->supported_rates,
	       sizeof(orig->supported_rates));
	v1->sta_index = orig->sta_index;
	v1->bssid_index = orig->bssid_index;
	v1->p2p = orig->p2p;
}
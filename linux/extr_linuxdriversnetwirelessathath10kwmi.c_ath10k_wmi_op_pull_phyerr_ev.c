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
struct wmi_phyerr_ev_arg {int hdr_len; int /*<<< orphan*/  phy_err_code; void** nf_chains; int /*<<< orphan*/  buf; void* buf_len; int /*<<< orphan*/  chan_width_mhz; int /*<<< orphan*/  rssi_combined; void* freq2; void* freq1; void* tsf_timestamp; } ;
struct wmi_phyerr {int phy_err_code; int /*<<< orphan*/ * nf_chains; int /*<<< orphan*/  buf; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  chan_width_mhz; int /*<<< orphan*/  rssi_combined; int /*<<< orphan*/  freq2; int /*<<< orphan*/  freq1; int /*<<< orphan*/  tsf_timestamp; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHY_ERROR_FALSE_RADAR_EXT ; 
#define  PHY_ERROR_GEN_FALSE_RADAR_EXT 130 
#define  PHY_ERROR_GEN_RADAR 129 
#define  PHY_ERROR_GEN_SPECTRAL_SCAN 128 
 int /*<<< orphan*/  PHY_ERROR_RADAR ; 
 int /*<<< orphan*/  PHY_ERROR_SPECTRAL_SCAN ; 
 int /*<<< orphan*/  PHY_ERROR_UNKNOWN ; 
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,int) ; 

int ath10k_wmi_op_pull_phyerr_ev(struct ath10k *ar,
				 const void *phyerr_buf,
				 int left_len,
				 struct wmi_phyerr_ev_arg *arg)
{
	const struct wmi_phyerr *phyerr = phyerr_buf;
	int i;

	if (left_len < sizeof(*phyerr)) {
		ath10k_warn(ar, "wrong phyerr event head len %d (need: >=%zd)\n",
			    left_len, sizeof(*phyerr));
		return -EINVAL;
	}

	arg->tsf_timestamp = __le32_to_cpu(phyerr->tsf_timestamp);
	arg->freq1 = __le16_to_cpu(phyerr->freq1);
	arg->freq2 = __le16_to_cpu(phyerr->freq2);
	arg->rssi_combined = phyerr->rssi_combined;
	arg->chan_width_mhz = phyerr->chan_width_mhz;
	arg->buf_len = __le32_to_cpu(phyerr->buf_len);
	arg->buf = phyerr->buf;
	arg->hdr_len = sizeof(*phyerr);

	for (i = 0; i < 4; i++)
		arg->nf_chains[i] = __le16_to_cpu(phyerr->nf_chains[i]);

	switch (phyerr->phy_err_code) {
	case PHY_ERROR_GEN_SPECTRAL_SCAN:
		arg->phy_err_code = PHY_ERROR_SPECTRAL_SCAN;
		break;
	case PHY_ERROR_GEN_FALSE_RADAR_EXT:
		arg->phy_err_code = PHY_ERROR_FALSE_RADAR_EXT;
		break;
	case PHY_ERROR_GEN_RADAR:
		arg->phy_err_code = PHY_ERROR_RADAR;
		break;
	default:
		arg->phy_err_code = PHY_ERROR_UNKNOWN;
		break;
	}

	return 0;
}
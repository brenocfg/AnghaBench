#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  int u16 ;
struct qtnf_hw_info {void* hw_version; int /*<<< orphan*/  fw_version; void* hw_capab; int /*<<< orphan*/  total_rx_chain; int /*<<< orphan*/  total_tx_chain; TYPE_3__* rd; int /*<<< orphan*/  mac_bitmap; void* fw_ver; int /*<<< orphan*/  max_scan_ssids; void* ql_proto_ver; int /*<<< orphan*/  num_mac; } ;
struct qtnf_bus {struct qtnf_hw_info hw_info; } ;
struct qlink_tlv_reg_rule {int /*<<< orphan*/  flags; int /*<<< orphan*/  dfs_cac_ms; int /*<<< orphan*/  max_eirp; int /*<<< orphan*/  max_antenna_gain; int /*<<< orphan*/  max_bandwidth_khz; int /*<<< orphan*/  end_freq_khz; int /*<<< orphan*/  start_freq_khz; } ;
struct qlink_tlv_hdr {int /*<<< orphan*/ * val; int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct qlink_resp_get_hw_info {int n_reg_rules; int dfs_region; scalar_t__ info; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  plat_id; int /*<<< orphan*/  bld_tmstamp; int /*<<< orphan*/ * alpha2; int /*<<< orphan*/  hw_capab; int /*<<< orphan*/  total_rx_chain; int /*<<< orphan*/  total_tx_chain; int /*<<< orphan*/  ql_proto_ver; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  mac_bitmap; int /*<<< orphan*/  num_mac; } ;
struct TYPE_6__ {void* max_eirp; void* max_antenna_gain; } ;
struct TYPE_5__ {void* max_bandwidth_khz; void* end_freq_khz; void* start_freq_khz; } ;
struct ieee80211_reg_rule {int /*<<< orphan*/  flags; void* dfs_cac_ms; TYPE_2__ power_rule; TYPE_1__ freq_range; } ;
struct TYPE_7__ {int n_reg_rules; int /*<<< orphan*/ * alpha2; struct ieee80211_reg_rule* reg_rules; int /*<<< orphan*/  dfs_region; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_DFS_ETSI ; 
 int /*<<< orphan*/  NL80211_DFS_FCC ; 
 int /*<<< orphan*/  NL80211_DFS_JP ; 
 int /*<<< orphan*/  NL80211_DFS_UNSET ; 
 int NL80211_MAX_SUPP_REG_RULES ; 
#define  QLINK_DFS_ETSI 140 
#define  QLINK_DFS_FCC 139 
#define  QLINK_DFS_JP 138 
#define  QLINK_DFS_UNSET 137 
#define  QTN_TLV_ID_BUILD_LABEL 136 
#define  QTN_TLV_ID_BUILD_NAME 135 
#define  QTN_TLV_ID_BUILD_REV 134 
#define  QTN_TLV_ID_BUILD_TYPE 133 
#define  QTN_TLV_ID_CALIBRATION_VER 132 
#define  QTN_TLV_ID_HW_ID 131 
#define  QTN_TLV_ID_MAX_SCAN_SSIDS 130 
#define  QTN_TLV_ID_REG_RULE 129 
#define  QTN_TLV_ID_UBOOT_VER 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,char const*,char const*,char const*,unsigned long,unsigned long,char const*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int,...) ; 
 int /*<<< orphan*/  qtnf_cmd_resp_reg_rule_flags_parse (void*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
qtnf_cmd_resp_proc_hw_info(struct qtnf_bus *bus,
			   const struct qlink_resp_get_hw_info *resp,
			   size_t info_len)
{
	struct qtnf_hw_info *hwinfo = &bus->hw_info;
	const struct qlink_tlv_hdr *tlv;
	const struct qlink_tlv_reg_rule *tlv_rule;
	const char *bld_name = NULL;
	const char *bld_rev = NULL;
	const char *bld_type = NULL;
	const char *bld_label = NULL;
	u32 bld_tmstamp = 0;
	u32 plat_id = 0;
	const char *hw_id = NULL;
	const char *calibration_ver = NULL;
	const char *uboot_ver = NULL;
	u32 hw_ver = 0;
	struct ieee80211_reg_rule *rule;
	u16 tlv_type;
	u16 tlv_value_len;
	unsigned int rule_idx = 0;

	if (WARN_ON(resp->n_reg_rules > NL80211_MAX_SUPP_REG_RULES))
		return -E2BIG;

	hwinfo->rd = kzalloc(sizeof(*hwinfo->rd)
			     + sizeof(struct ieee80211_reg_rule)
			     * resp->n_reg_rules, GFP_KERNEL);

	if (!hwinfo->rd)
		return -ENOMEM;

	hwinfo->num_mac = resp->num_mac;
	hwinfo->mac_bitmap = resp->mac_bitmap;
	hwinfo->fw_ver = le32_to_cpu(resp->fw_ver);
	hwinfo->ql_proto_ver = le16_to_cpu(resp->ql_proto_ver);
	hwinfo->total_tx_chain = resp->total_tx_chain;
	hwinfo->total_rx_chain = resp->total_rx_chain;
	hwinfo->hw_capab = le32_to_cpu(resp->hw_capab);
	hwinfo->rd->n_reg_rules = resp->n_reg_rules;
	hwinfo->rd->alpha2[0] = resp->alpha2[0];
	hwinfo->rd->alpha2[1] = resp->alpha2[1];

	bld_tmstamp = le32_to_cpu(resp->bld_tmstamp);
	plat_id = le32_to_cpu(resp->plat_id);
	hw_ver = le32_to_cpu(resp->hw_ver);

	switch (resp->dfs_region) {
	case QLINK_DFS_FCC:
		hwinfo->rd->dfs_region = NL80211_DFS_FCC;
		break;
	case QLINK_DFS_ETSI:
		hwinfo->rd->dfs_region = NL80211_DFS_ETSI;
		break;
	case QLINK_DFS_JP:
		hwinfo->rd->dfs_region = NL80211_DFS_JP;
		break;
	case QLINK_DFS_UNSET:
	default:
		hwinfo->rd->dfs_region = NL80211_DFS_UNSET;
		break;
	}

	tlv = (const struct qlink_tlv_hdr *)resp->info;

	while (info_len >= sizeof(*tlv)) {
		tlv_type = le16_to_cpu(tlv->type);
		tlv_value_len = le16_to_cpu(tlv->len);

		if (tlv_value_len + sizeof(*tlv) > info_len) {
			pr_warn("malformed TLV 0x%.2X; LEN: %u\n",
				tlv_type, tlv_value_len);
			return -EINVAL;
		}

		switch (tlv_type) {
		case QTN_TLV_ID_REG_RULE:
			if (rule_idx >= resp->n_reg_rules) {
				pr_warn("unexpected number of rules: %u\n",
					resp->n_reg_rules);
				return -EINVAL;
			}

			if (tlv_value_len != sizeof(*tlv_rule) - sizeof(*tlv)) {
				pr_warn("malformed TLV 0x%.2X; LEN: %u\n",
					tlv_type, tlv_value_len);
				return -EINVAL;
			}

			tlv_rule = (const struct qlink_tlv_reg_rule *)tlv;
			rule = &hwinfo->rd->reg_rules[rule_idx++];

			rule->freq_range.start_freq_khz =
				le32_to_cpu(tlv_rule->start_freq_khz);
			rule->freq_range.end_freq_khz =
				le32_to_cpu(tlv_rule->end_freq_khz);
			rule->freq_range.max_bandwidth_khz =
				le32_to_cpu(tlv_rule->max_bandwidth_khz);
			rule->power_rule.max_antenna_gain =
				le32_to_cpu(tlv_rule->max_antenna_gain);
			rule->power_rule.max_eirp =
				le32_to_cpu(tlv_rule->max_eirp);
			rule->dfs_cac_ms =
				le32_to_cpu(tlv_rule->dfs_cac_ms);
			rule->flags = qtnf_cmd_resp_reg_rule_flags_parse(
					le32_to_cpu(tlv_rule->flags));
			break;
		case QTN_TLV_ID_BUILD_NAME:
			bld_name = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_BUILD_REV:
			bld_rev = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_BUILD_TYPE:
			bld_type = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_BUILD_LABEL:
			bld_label = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_HW_ID:
			hw_id = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_CALIBRATION_VER:
			calibration_ver = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_UBOOT_VER:
			uboot_ver = (const void *)tlv->val;
			break;
		case QTN_TLV_ID_MAX_SCAN_SSIDS:
			hwinfo->max_scan_ssids = *tlv->val;
			break;
		default:
			break;
		}

		info_len -= tlv_value_len + sizeof(*tlv);
		tlv = (struct qlink_tlv_hdr *)(tlv->val + tlv_value_len);
	}

	if (rule_idx != resp->n_reg_rules) {
		pr_warn("unexpected number of rules: expected %u got %u\n",
			resp->n_reg_rules, rule_idx);
		kfree(hwinfo->rd);
		hwinfo->rd = NULL;
		return -EINVAL;
	}

	pr_info("fw_version=%d, MACs map %#x, alpha2=\"%c%c\", chains Tx=%u Rx=%u, capab=0x%x\n",
		hwinfo->fw_ver, hwinfo->mac_bitmap,
		hwinfo->rd->alpha2[0], hwinfo->rd->alpha2[1],
		hwinfo->total_tx_chain, hwinfo->total_rx_chain,
		hwinfo->hw_capab);

	pr_info("\nBuild name:            %s"  \
		"\nBuild revision:        %s"  \
		"\nBuild type:            %s"  \
		"\nBuild label:           %s"  \
		"\nBuild timestamp:       %lu" \
		"\nPlatform ID:           %lu" \
		"\nHardware ID:           %s"  \
		"\nCalibration version:   %s"  \
		"\nU-Boot version:        %s"  \
		"\nHardware version:      0x%08x",
		bld_name, bld_rev, bld_type, bld_label,
		(unsigned long)bld_tmstamp,
		(unsigned long)plat_id,
		hw_id, calibration_ver, uboot_ver, hw_ver);

	strlcpy(hwinfo->fw_version, bld_label, sizeof(hwinfo->fw_version));
	hwinfo->hw_version = hw_ver;

	return 0;
}
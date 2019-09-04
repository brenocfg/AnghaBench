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
struct wiphy_wowlan_support {int flags; void* pattern_min_len; void* pattern_max_len; void* n_patterns; } ;
struct qtnf_mac_info {struct wiphy_wowlan_support* wowlan; } ;
struct qtnf_wmac {int /*<<< orphan*/  macid; struct qtnf_mac_info macinfo; } ;
struct qlink_wowlan_support {int /*<<< orphan*/  pattern_min_len; int /*<<< orphan*/  pattern_max_len; int /*<<< orphan*/  n_patterns; } ;
struct qlink_wowlan_capab_data {int /*<<< orphan*/  version; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WIPHY_WOWLAN_DISCONNECT ; 
 int WIPHY_WOWLAN_MAGIC_PKT ; 
 int /*<<< orphan*/  kfree (struct wiphy_wowlan_support*) ; 
 struct wiphy_wowlan_support* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qtnf_parse_wowlan_info(struct qtnf_wmac *mac,
		       const struct qlink_wowlan_capab_data *wowlan)
{
	struct qtnf_mac_info *mac_info = &mac->macinfo;
	const struct qlink_wowlan_support *data1;
	struct wiphy_wowlan_support *supp;

	supp = kzalloc(sizeof(*supp), GFP_KERNEL);
	if (!supp)
		return;

	switch (le16_to_cpu(wowlan->version)) {
	case 0x1:
		data1 = (struct qlink_wowlan_support *)wowlan->data;

		supp->flags = WIPHY_WOWLAN_MAGIC_PKT | WIPHY_WOWLAN_DISCONNECT;
		supp->n_patterns = le32_to_cpu(data1->n_patterns);
		supp->pattern_max_len = le32_to_cpu(data1->pattern_max_len);
		supp->pattern_min_len = le32_to_cpu(data1->pattern_min_len);

		mac_info->wowlan = supp;
		break;
	default:
		pr_warn("MAC%u: unsupported WoWLAN version 0x%x\n",
			mac->macid, le16_to_cpu(wowlan->version));
		kfree(supp);
		break;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {struct cfg80211_pmsr_capabilities* pmsr_capa; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;
struct cfg80211_pmsr_capabilities {scalar_t__ randomize_mac_addr; scalar_t__ report_ap_tsf; int /*<<< orphan*/  max_peers; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  NL80211_ATTR_PEER_MEASUREMENTS ; 
 int /*<<< orphan*/  NL80211_PMSR_ATTR_MAX_PEERS ; 
 int /*<<< orphan*/  NL80211_PMSR_ATTR_RANDOMIZE_MAC_ADDR ; 
 int /*<<< orphan*/  NL80211_PMSR_ATTR_REPORT_AP_TSF ; 
 int /*<<< orphan*/  NL80211_PMSR_ATTR_TYPE_CAPA ; 
 scalar_t__ nl80211_send_pmsr_ftm_capa (struct cfg80211_pmsr_capabilities const*,struct sk_buff*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_send_pmsr_capa(struct cfg80211_registered_device *rdev,
				  struct sk_buff *msg)
{
	const struct cfg80211_pmsr_capabilities *cap = rdev->wiphy.pmsr_capa;
	struct nlattr *pmsr, *caps;

	if (!cap)
		return 0;

	/*
	 * we don't need to clean up anything here since the caller
	 * will genlmsg_cancel() if we fail
	 */

	pmsr = nla_nest_start_noflag(msg, NL80211_ATTR_PEER_MEASUREMENTS);
	if (!pmsr)
		return -ENOBUFS;

	if (nla_put_u32(msg, NL80211_PMSR_ATTR_MAX_PEERS, cap->max_peers))
		return -ENOBUFS;

	if (cap->report_ap_tsf &&
	    nla_put_flag(msg, NL80211_PMSR_ATTR_REPORT_AP_TSF))
		return -ENOBUFS;

	if (cap->randomize_mac_addr &&
	    nla_put_flag(msg, NL80211_PMSR_ATTR_RANDOMIZE_MAC_ADDR))
		return -ENOBUFS;

	caps = nla_nest_start_noflag(msg, NL80211_PMSR_ATTR_TYPE_CAPA);
	if (!caps)
		return -ENOBUFS;

	if (nl80211_send_pmsr_ftm_capa(cap, msg))
		return -ENOBUFS;

	nla_nest_end(msg, caps);
	nla_nest_end(msg, pmsr);

	return 0;
}
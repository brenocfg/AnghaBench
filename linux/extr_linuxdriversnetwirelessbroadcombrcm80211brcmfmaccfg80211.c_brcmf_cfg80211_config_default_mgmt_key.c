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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_if {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_FEAT_MFP ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ brcmf_feat_is_enabled (struct brcmf_if*,int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static s32
brcmf_cfg80211_config_default_mgmt_key(struct wiphy *wiphy,
				       struct net_device *ndev, u8 key_idx)
{
	struct brcmf_if *ifp = netdev_priv(ndev);

	brcmf_dbg(TRACE, "Enter key_idx %d\n", key_idx);

	if (brcmf_feat_is_enabled(ifp, BRCMF_FEAT_MFP))
		return 0;

	brcmf_dbg(INFO, "Not supported\n");

	return -EOPNOTSUPP;
}
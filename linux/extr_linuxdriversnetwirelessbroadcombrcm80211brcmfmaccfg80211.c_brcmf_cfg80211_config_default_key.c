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
typedef  int u8 ;
typedef  int u32 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_if {int /*<<< orphan*/  vif; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_KEY_PRIMARY ; 
 int /*<<< orphan*/  CONN ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  TRACE ; 
 int WEP_ENABLED ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (char*,scalar_t__) ; 
 scalar_t__ brcmf_fil_bsscfg_int_get (struct brcmf_if*,char*,int*) ; 
 scalar_t__ brcmf_fil_cmd_int_set (struct brcmf_if*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_vif_up (int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static s32
brcmf_cfg80211_config_default_key(struct wiphy *wiphy, struct net_device *ndev,
				  u8 key_idx, bool unicast, bool multicast)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	u32 index;
	u32 wsec;
	s32 err = 0;

	brcmf_dbg(TRACE, "Enter\n");
	brcmf_dbg(CONN, "key index (%d)\n", key_idx);
	if (!check_vif_up(ifp->vif))
		return -EIO;

	err = brcmf_fil_bsscfg_int_get(ifp, "wsec", &wsec);
	if (err) {
		brcmf_err("WLC_GET_WSEC error (%d)\n", err);
		goto done;
	}

	if (wsec & WEP_ENABLED) {
		/* Just select a new current key */
		index = key_idx;
		err = brcmf_fil_cmd_int_set(ifp,
					    BRCMF_C_SET_KEY_PRIMARY, index);
		if (err)
			brcmf_err("error (%d)\n", err);
	}
done:
	brcmf_dbg(TRACE, "Exit\n");
	return err;
}
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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct brcmf_wsec_key {scalar_t__ algo; int /*<<< orphan*/  flags; scalar_t__ index; } ;
struct brcmf_if {TYPE_2__* vif; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_3__ {struct brcmf_wsec_key* key; } ;
struct TYPE_4__ {TYPE_1__ profile; } ;

/* Variables and functions */
 size_t BRCMF_MAX_DEFAULT_KEYS ; 
 int /*<<< orphan*/  BRCMF_PRIMARY_KEY ; 
 int /*<<< orphan*/  CONN ; 
 scalar_t__ CRYPTO_ALGO_OFF ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  check_vif_up (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (struct brcmf_wsec_key*,int /*<<< orphan*/ ,int) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  send_key_to_dongle (struct brcmf_if*,struct brcmf_wsec_key*) ; 

__attribute__((used)) static s32
brcmf_cfg80211_del_key(struct wiphy *wiphy, struct net_device *ndev,
		       u8 key_idx, bool pairwise, const u8 *mac_addr)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_wsec_key *key;
	s32 err;

	brcmf_dbg(TRACE, "Enter\n");
	brcmf_dbg(CONN, "key index (%d)\n", key_idx);

	if (!check_vif_up(ifp->vif))
		return -EIO;

	if (key_idx >= BRCMF_MAX_DEFAULT_KEYS) {
		/* we ignore this key index in this case */
		return -EINVAL;
	}

	key = &ifp->vif->profile.key[key_idx];

	if (key->algo == CRYPTO_ALGO_OFF) {
		brcmf_dbg(CONN, "Ignore clearing of (never configured) key\n");
		return -EINVAL;
	}

	memset(key, 0, sizeof(*key));
	key->index = (u32)key_idx;
	key->flags = BRCMF_PRIMARY_KEY;

	/* Clear the key/index */
	err = send_key_to_dongle(ifp, key);

	brcmf_dbg(TRACE, "Exit\n");
	return err;
}
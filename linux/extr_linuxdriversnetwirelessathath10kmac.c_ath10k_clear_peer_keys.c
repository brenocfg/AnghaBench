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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct ath10k_peer {int /*<<< orphan*/ ** keys; } ;
struct ath10k {int /*<<< orphan*/  data_lock; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DISABLE_KEY ; 
 int ENOENT ; 
 int ath10k_install_key (struct ath10k_vif*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct ath10k_peer* ath10k_peer_find (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_clear_peer_keys(struct ath10k_vif *arvif,
				  const u8 *addr)
{
	struct ath10k *ar = arvif->ar;
	struct ath10k_peer *peer;
	int first_errno = 0;
	int ret;
	int i;
	u32 flags = 0;

	lockdep_assert_held(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, arvif->vdev_id, addr);
	spin_unlock_bh(&ar->data_lock);

	if (!peer)
		return -ENOENT;

	for (i = 0; i < ARRAY_SIZE(peer->keys); i++) {
		if (peer->keys[i] == NULL)
			continue;

		/* key flags are not required to delete the key */
		ret = ath10k_install_key(arvif, peer->keys[i],
					 DISABLE_KEY, addr, flags);
		if (ret < 0 && first_errno == 0)
			first_errno = ret;

		if (ret < 0)
			ath10k_warn(ar, "failed to remove peer wep key %d: %d\n",
				    i, ret);

		spin_lock_bh(&ar->data_lock);
		peer->keys[i] = NULL;
		spin_unlock_bh(&ar->data_lock);
	}

	return first_errno;
}
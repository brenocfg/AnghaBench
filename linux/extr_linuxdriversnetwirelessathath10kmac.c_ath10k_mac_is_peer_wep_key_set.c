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
typedef  scalar_t__ u8 ;
struct ath10k_peer {TYPE_1__** keys; } ;
struct ath10k {int /*<<< orphan*/  data_lock; } ;
struct TYPE_2__ {scalar_t__ keyidx; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 struct ath10k_peer* ath10k_peer_find (struct ath10k*,int /*<<< orphan*/ ,scalar_t__ const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

bool ath10k_mac_is_peer_wep_key_set(struct ath10k *ar, const u8 *addr,
				    u8 keyidx)
{
	struct ath10k_peer *peer;
	int i;

	lockdep_assert_held(&ar->data_lock);

	/* We don't know which vdev this peer belongs to,
	 * since WMI doesn't give us that information.
	 *
	 * FIXME: multi-bss needs to be handled.
	 */
	peer = ath10k_peer_find(ar, 0, addr);
	if (!peer)
		return false;

	for (i = 0; i < ARRAY_SIZE(peer->keys); i++) {
		if (peer->keys[i] && peer->keys[i]->keyidx == keyidx)
			return true;
	}

	return false;
}
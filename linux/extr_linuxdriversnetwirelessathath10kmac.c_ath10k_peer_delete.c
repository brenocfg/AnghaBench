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
struct ath10k {int /*<<< orphan*/  num_peers; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int ath10k_wait_for_peer_deleted (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int ath10k_wmi_peer_delete (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_peer_delete(struct ath10k *ar, u32 vdev_id, const u8 *addr)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath10k_wmi_peer_delete(ar, vdev_id, addr);
	if (ret)
		return ret;

	ret = ath10k_wait_for_peer_deleted(ar, vdev_id, addr);
	if (ret)
		return ret;

	ar->num_peers--;

	return 0;
}
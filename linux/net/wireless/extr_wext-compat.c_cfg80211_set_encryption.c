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
struct net_device {int /*<<< orphan*/  ieee80211_ptr; } ;
struct key_params {int dummy; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int __cfg80211_set_encryption (struct cfg80211_registered_device*,struct net_device*,int,int /*<<< orphan*/  const*,int,int,int,struct key_params*) ; 
 int /*<<< orphan*/  wdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdev_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_set_encryption(struct cfg80211_registered_device *rdev,
				   struct net_device *dev, bool pairwise,
				   const u8 *addr, bool remove, bool tx_key,
				   int idx, struct key_params *params)
{
	int err;

	wdev_lock(dev->ieee80211_ptr);
	err = __cfg80211_set_encryption(rdev, dev, pairwise, addr,
					remove, tx_key, idx, params);
	wdev_unlock(dev->ieee80211_ptr);

	return err;
}
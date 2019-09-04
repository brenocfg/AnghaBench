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
typedef  int /*<<< orphan*/  u64 ;
struct ieee80211_hw {int dummy; } ;
struct b43_wldev {int dummy; } ;
struct b43_wl {unsigned int filter_flags; int /*<<< orphan*/  mutex; struct b43_wldev* current_dev; } ;

/* Variables and functions */
 scalar_t__ B43_STAT_INITIALIZED ; 
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_BCN_PRBRESP_PROMISC ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_FCSFAIL ; 
 unsigned int FIF_OTHER_BSS ; 
 unsigned int FIF_PLCPFAIL ; 
 int /*<<< orphan*/  b43_adjust_opmode (struct b43_wldev*) ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_op_configure_filter(struct ieee80211_hw *hw,
				    unsigned int changed, unsigned int *fflags,
				    u64 multicast)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);
	struct b43_wldev *dev;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	if (!dev) {
		*fflags = 0;
		goto out_unlock;
	}

	*fflags &= FIF_ALLMULTI |
		  FIF_FCSFAIL |
		  FIF_PLCPFAIL |
		  FIF_CONTROL |
		  FIF_OTHER_BSS |
		  FIF_BCN_PRBRESP_PROMISC;

	changed &= FIF_ALLMULTI |
		   FIF_FCSFAIL |
		   FIF_PLCPFAIL |
		   FIF_CONTROL |
		   FIF_OTHER_BSS |
		   FIF_BCN_PRBRESP_PROMISC;

	wl->filter_flags = *fflags;

	if (changed && b43_status(dev) >= B43_STAT_INITIALIZED)
		b43_adjust_opmode(dev);

out_unlock:
	mutex_unlock(&wl->mutex);
}
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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {int e; int m; } ;
struct hostap_interface {TYPE_2__* local; } ;
struct TYPE_4__ {int channel_mask; int channel; TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_3__ {scalar_t__ (* reset_port ) (struct net_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int FREQ_COUNT ; 
 int /*<<< orphan*/  HFA384X_RID_CNFOWNCHANNEL ; 
 int* freq_list ; 
 scalar_t__ hostap_set_word (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*) ; 

__attribute__((used)) static int prism2_ioctl_siwfreq(struct net_device *dev,
				struct iw_request_info *info,
				struct iw_freq *freq, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;

	iface = netdev_priv(dev);
	local = iface->local;

	/* freq => chan. */
	if (freq->e == 1 &&
	    freq->m / 100000 >= freq_list[0] &&
	    freq->m / 100000 <= freq_list[FREQ_COUNT - 1]) {
		int ch;
		int fr = freq->m / 100000;
		for (ch = 0; ch < FREQ_COUNT; ch++) {
			if (fr == freq_list[ch]) {
				freq->e = 0;
				freq->m = ch + 1;
				break;
			}
		}
	}

	if (freq->e != 0 || freq->m < 1 || freq->m > FREQ_COUNT ||
	    !(local->channel_mask & (1 << (freq->m - 1))))
		return -EINVAL;

	local->channel = freq->m; /* channel is used in prism2_setup_rids() */
	if (hostap_set_word(dev, HFA384X_RID_CNFOWNCHANNEL, local->channel) ||
	    local->func->reset_port(dev))
		return -EINVAL;

	return 0;
}
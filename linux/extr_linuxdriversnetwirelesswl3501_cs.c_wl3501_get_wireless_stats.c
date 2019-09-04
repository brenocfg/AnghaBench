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
typedef  int /*<<< orphan*/  value ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  misc; scalar_t__ retries; int /*<<< orphan*/  code; } ;
struct iw_statistics {TYPE_1__ discard; int /*<<< orphan*/  status; } ;
struct wl3501_card {struct iw_statistics wstats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL3501_MIB_ATTR_ACK_FAILURE_COUNT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_FAILED_COUNT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_FRAME_DUPLICATE_COUNT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_RETRY_COUNT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_RTS_FAILURE_COUNT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_WEP_EXCLUDED_COUNT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_WEP_ICV_ERROR_COUNT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_WEP_UNDECRYPTABLE_COUNT ; 
 int /*<<< orphan*/  memset (struct iw_statistics*,int /*<<< orphan*/ ,int) ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  wl3501_get_mib_value (struct wl3501_card*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static struct iw_statistics *wl3501_get_wireless_stats(struct net_device *dev)
{
	struct wl3501_card *this = netdev_priv(dev);
	struct iw_statistics *wstats = &this->wstats;
	u32 value; /* size checked: it is u32 */

	memset(wstats, 0, sizeof(*wstats));
	wstats->status = netif_running(dev);
	if (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_WEP_ICV_ERROR_COUNT,
				  &value, sizeof(value)))
		wstats->discard.code += value;
	if (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_WEP_UNDECRYPTABLE_COUNT,
				  &value, sizeof(value)))
		wstats->discard.code += value;
	if (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_WEP_EXCLUDED_COUNT,
				  &value, sizeof(value)))
		wstats->discard.code += value;
	if (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_RETRY_COUNT,
				  &value, sizeof(value)))
		wstats->discard.retries	= value;
	if (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_FAILED_COUNT,
				  &value, sizeof(value)))
		wstats->discard.misc += value;
	if (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_RTS_FAILURE_COUNT,
				  &value, sizeof(value)))
		wstats->discard.misc += value;
	if (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_ACK_FAILURE_COUNT,
				  &value, sizeof(value)))
		wstats->discard.misc += value;
	if (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_FRAME_DUPLICATE_COUNT,
				  &value, sizeof(value)))
		wstats->discard.misc += value;
	return wstats;
}
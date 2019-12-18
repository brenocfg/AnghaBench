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
typedef  int /*<<< orphan*/  wrqu ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
union iwreq_data {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct net_device {TYPE_2__* ieee80211_ptr; } ;
struct cfg80211_registered_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nl80211_key_type { ____Placeholder_nl80211_key_type } nl80211_key_type ;
struct TYPE_4__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWEVCUSTOM ; 
 int NL80211_KEYTYPE_GROUP ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl80211_michael_mic_failure (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  trace_cfg80211_michael_mic_failure (struct net_device*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const*) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,char*) ; 

void cfg80211_michael_mic_failure(struct net_device *dev, const u8 *addr,
				  enum nl80211_key_type key_type, int key_id,
				  const u8 *tsc, gfp_t gfp)
{
	struct wiphy *wiphy = dev->ieee80211_ptr->wiphy;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);
#ifdef CONFIG_CFG80211_WEXT
	union iwreq_data wrqu;
	char *buf = kmalloc(128, gfp);

	if (buf) {
		sprintf(buf, "MLME-MICHAELMICFAILURE.indication("
			"keyid=%d %scast addr=%pM)", key_id,
			key_type == NL80211_KEYTYPE_GROUP ? "broad" : "uni",
			addr);
		memset(&wrqu, 0, sizeof(wrqu));
		wrqu.data.length = strlen(buf);
		wireless_send_event(dev, IWEVCUSTOM, &wrqu, buf);
		kfree(buf);
	}
#endif

	trace_cfg80211_michael_mic_failure(dev, addr, key_type, key_id, tsc);
	nl80211_michael_mic_failure(rdev, dev, addr, key_type, key_id, tsc, gfp);
}
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
struct TYPE_4__ {int length; } ;
union iwreq_data {TYPE_2__ data; } ;
typedef  int u8 ;
struct hermes {TYPE_1__* ops; } ;
struct orinoco_private {int /*<<< orphan*/  has_wpa; struct hermes hw; struct net_device* ndev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int (* read_ltv ) (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HERMES_RID_CURRENT_ASSOC_RESP_INFO ; 
 int /*<<< orphan*/  IWEVASSOCRESPIE ; 
 int /*<<< orphan*/  USER_BAP ; 
 int* orinoco_get_wpa_ie (int*,int) ; 
 int stub1 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int**) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int*) ; 

__attribute__((used)) static void orinoco_send_assocrespie_wevent(struct orinoco_private *priv)
{
	struct net_device *dev = priv->ndev;
	struct hermes *hw = &priv->hw;
	union iwreq_data wrqu;
	int err;
	u8 buf[88]; /* TODO: verify max size or IW_GENERIC_IE_MAX */
	u8 *ie;

	if (!priv->has_wpa)
		return;

	err = hw->ops->read_ltv(hw, USER_BAP,
				HERMES_RID_CURRENT_ASSOC_RESP_INFO,
				sizeof(buf), NULL, &buf);
	if (err != 0)
		return;

	ie = orinoco_get_wpa_ie(buf, sizeof(buf));
	if (ie) {
		int rem = sizeof(buf) - (ie - &buf[0]);
		wrqu.data.length = ie[1] + 2;
		if (wrqu.data.length > rem)
			wrqu.data.length = rem;

		if (wrqu.data.length)
			/* Send event to user space */
			wireless_send_event(dev, IWEVASSOCRESPIE, &wrqu, ie);
	}
}
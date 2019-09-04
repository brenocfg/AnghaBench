#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct brcmf_if_event {int action; int /*<<< orphan*/  bsscfgidx; int /*<<< orphan*/  ifidx; int /*<<< orphan*/  flags; } ;
struct brcmf_if {TYPE_3__* ndev; struct brcmf_cfg80211_vif* vif; TYPE_1__* drvr; } ;
struct brcmf_event_msg {int dummy; } ;
struct brcmf_cfg80211_vif_event {int action; int /*<<< orphan*/  vif_event_lock; int /*<<< orphan*/  vif_wq; struct brcmf_cfg80211_vif* vif; } ;
struct TYPE_5__ {TYPE_3__* netdev; } ;
struct brcmf_cfg80211_vif {TYPE_2__ wdev; struct brcmf_if* ifp; } ;
struct brcmf_cfg80211_info {int /*<<< orphan*/  wiphy; struct brcmf_cfg80211_vif_event vif_event; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_6__ {TYPE_2__* ieee80211_ptr; } ;
struct TYPE_4__ {struct brcmf_cfg80211_info* config; } ;

/* Variables and functions */
#define  BRCMF_E_IF_ADD 130 
#define  BRCMF_E_IF_CHANGE 129 
#define  BRCMF_E_IF_DEL 128 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_cfg80211_vif_event_armed (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 brcmf_notify_vif_event(struct brcmf_if *ifp,
				  const struct brcmf_event_msg *e, void *data)
{
	struct brcmf_cfg80211_info *cfg = ifp->drvr->config;
	struct brcmf_if_event *ifevent = (struct brcmf_if_event *)data;
	struct brcmf_cfg80211_vif_event *event = &cfg->vif_event;
	struct brcmf_cfg80211_vif *vif;

	brcmf_dbg(TRACE, "Enter: action %u flags %u ifidx %u bsscfgidx %u\n",
		  ifevent->action, ifevent->flags, ifevent->ifidx,
		  ifevent->bsscfgidx);

	spin_lock(&event->vif_event_lock);
	event->action = ifevent->action;
	vif = event->vif;

	switch (ifevent->action) {
	case BRCMF_E_IF_ADD:
		/* waiting process may have timed out */
		if (!cfg->vif_event.vif) {
			spin_unlock(&event->vif_event_lock);
			return -EBADF;
		}

		ifp->vif = vif;
		vif->ifp = ifp;
		if (ifp->ndev) {
			vif->wdev.netdev = ifp->ndev;
			ifp->ndev->ieee80211_ptr = &vif->wdev;
			SET_NETDEV_DEV(ifp->ndev, wiphy_dev(cfg->wiphy));
		}
		spin_unlock(&event->vif_event_lock);
		wake_up(&event->vif_wq);
		return 0;

	case BRCMF_E_IF_DEL:
		spin_unlock(&event->vif_event_lock);
		/* event may not be upon user request */
		if (brcmf_cfg80211_vif_event_armed(cfg))
			wake_up(&event->vif_wq);
		return 0;

	case BRCMF_E_IF_CHANGE:
		spin_unlock(&event->vif_event_lock);
		wake_up(&event->vif_wq);
		return 0;

	default:
		spin_unlock(&event->vif_event_lock);
		break;
	}
	return -EINVAL;
}
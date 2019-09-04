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
struct brcmf_cfg80211_vif_event {int /*<<< orphan*/  vif_event_lock; int /*<<< orphan*/ * vif; } ;
struct brcmf_cfg80211_info {struct brcmf_cfg80211_vif_event vif_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool brcmf_cfg80211_vif_event_armed(struct brcmf_cfg80211_info *cfg)
{
	struct brcmf_cfg80211_vif_event *event = &cfg->vif_event;
	bool armed;

	spin_lock(&event->vif_event_lock);
	armed = event->vif != NULL;
	spin_unlock(&event->vif_event_lock);

	return armed;
}
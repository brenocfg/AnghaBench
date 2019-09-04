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
struct hidden_network {int n_ssids; struct hidden_net_info* net_info; } ;
struct hidden_net_info {scalar_t__ ssid_len; struct hidden_net_info* ssid; } ;
struct cfg80211_scan_request {int n_ssids; TYPE_1__* ssids; } ;
struct TYPE_2__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hidden_net_info* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hidden_net_info*) ; 
 struct hidden_net_info* kmemdup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
wilc_wfi_cfg_alloc_fill_ssid(struct cfg80211_scan_request *request,
			     struct hidden_network *ntwk)
{
	int i;
	int slot_id = 0;

	ntwk->net_info = kcalloc(request->n_ssids, sizeof(*ntwk->net_info),
				 GFP_KERNEL);
	if (!ntwk->net_info)
		goto out;

	ntwk->n_ssids = request->n_ssids;

	for (i = 0; i < request->n_ssids; i++) {
		if (request->ssids[i].ssid_len > 0) {
			struct hidden_net_info *info = &ntwk->net_info[slot_id];

			info->ssid = kmemdup(request->ssids[i].ssid,
					     request->ssids[i].ssid_len,
					     GFP_KERNEL);
			if (!info->ssid)
				goto out_free;

			info->ssid_len = request->ssids[i].ssid_len;
			slot_id++;
		} else {
			ntwk->n_ssids -= 1;
		}
	}
	return 0;

out_free:

	for (i = 0; i < slot_id; i++)
		kfree(ntwk->net_info[i].ssid);

	kfree(ntwk->net_info);
out:

	return -ENOMEM;
}
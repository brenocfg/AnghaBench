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
struct wireless_dev {int dummy; } ;
struct wil6210_vif {scalar_t__ mid; } ;
struct wil6210_priv {struct wireless_dev* radio_wdev; } ;

/* Variables and functions */
 struct wireless_dev* vif_to_wdev (struct wil6210_vif*) ; 

__attribute__((used)) static inline struct wireless_dev *
vif_to_radio_wdev(struct wil6210_priv *wil, struct wil6210_vif *vif)
{
	/* main interface is shared with P2P device */
	if (vif->mid)
		return vif_to_wdev(vif);
	else
		return wil->radio_wdev;
}
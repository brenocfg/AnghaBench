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
struct cfg80211_nan_func {int num_rx_filters; int num_tx_filters; struct cfg80211_nan_func* tx_filters; struct cfg80211_nan_func* rx_filters; struct cfg80211_nan_func* filter; struct cfg80211_nan_func* srf_macs; struct cfg80211_nan_func* srf_bf; struct cfg80211_nan_func* serv_spec_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cfg80211_nan_func*) ; 

void cfg80211_free_nan_func(struct cfg80211_nan_func *f)
{
	int i;

	if (!f)
		return;

	kfree(f->serv_spec_info);
	kfree(f->srf_bf);
	kfree(f->srf_macs);
	for (i = 0; i < f->num_rx_filters; i++)
		kfree(f->rx_filters[i].filter);

	for (i = 0; i < f->num_tx_filters; i++)
		kfree(f->tx_filters[i].filter);

	kfree(f->rx_filters);
	kfree(f->tx_filters);
	kfree(f);
}
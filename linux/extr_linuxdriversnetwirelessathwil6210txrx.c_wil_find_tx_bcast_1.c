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
struct wil_ring_tx_data {int /*<<< orphan*/  dot1x_open; int /*<<< orphan*/  enabled; } ;
struct wil_ring {int /*<<< orphan*/  va; } ;
struct wil6210_vif {int bcast_ring; } ;
struct wil6210_priv {struct wil_ring_tx_data* ring_tx_data; struct wil_ring* ring_tx; } ;
struct sk_buff {scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PAE ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wil_ring *wil_find_tx_bcast_1(struct wil6210_priv *wil,
					    struct wil6210_vif *vif,
					    struct sk_buff *skb)
{
	struct wil_ring *v;
	struct wil_ring_tx_data *txdata;
	int i = vif->bcast_ring;

	if (i < 0)
		return NULL;
	v = &wil->ring_tx[i];
	txdata = &wil->ring_tx_data[i];
	if (!v->va || !txdata->enabled)
		return NULL;
	if (!wil->ring_tx_data[i].dot1x_open &&
	    skb->protocol != cpu_to_be16(ETH_P_PAE))
		return NULL;

	return v;
}
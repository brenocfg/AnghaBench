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
struct wil_net_stats {int /*<<< orphan*/  rx_mic_error; } ;
struct wil6210_priv {int dummy; } ;
struct TYPE_2__ {int status; int error; } ;
struct vring_rx_desc {TYPE_1__ dma; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int RX_DMA_ERROR_MIC ; 
 int RX_DMA_STATUS_ERROR ; 
 int /*<<< orphan*/  wil_dbg_txrx (struct wil6210_priv*,char*) ; 
 struct vring_rx_desc* wil_skb_rxdesc (struct sk_buff*) ; 

__attribute__((used)) static int wil_rx_error_check(struct wil6210_priv *wil, struct sk_buff *skb,
			      struct wil_net_stats *stats)
{
	struct vring_rx_desc *d = wil_skb_rxdesc(skb);

	if ((d->dma.status & RX_DMA_STATUS_ERROR) &&
	    (d->dma.error & RX_DMA_ERROR_MIC)) {
		stats->rx_mic_error++;
		wil_dbg_txrx(wil, "MIC error, dropping packet\n");
		return -EFAULT;
	}

	return 0;
}
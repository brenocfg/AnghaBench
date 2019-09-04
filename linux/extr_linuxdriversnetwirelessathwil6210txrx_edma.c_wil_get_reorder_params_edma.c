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
typedef  int /*<<< orphan*/  u16 ;
struct wil_rx_status_extended {int dummy; } ;
struct wil6210_priv {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int wil_rx_status_get_cid (struct wil_rx_status_extended*) ; 
 int wil_rx_status_get_mcast (struct wil_rx_status_extended*) ; 
 int wil_rx_status_get_mid (struct wil_rx_status_extended*) ; 
 int wil_rx_status_get_retry (struct wil_rx_status_extended*) ; 
 int /*<<< orphan*/  wil_rx_status_get_seq (struct wil6210_priv*,struct wil_rx_status_extended*) ; 
 int wil_rx_status_get_tid (struct wil_rx_status_extended*) ; 
 struct wil_rx_status_extended* wil_skb_rxstatus (struct sk_buff*) ; 

__attribute__((used)) static void wil_get_reorder_params_edma(struct wil6210_priv *wil,
					struct sk_buff *skb, int *tid,
					int *cid, int *mid, u16 *seq,
					int *mcast, int *retry)
{
	struct wil_rx_status_extended *s = wil_skb_rxstatus(skb);

	*tid = wil_rx_status_get_tid(s);
	*cid = wil_rx_status_get_cid(s);
	*mid = wil_rx_status_get_mid(s);
	*seq = le16_to_cpu(wil_rx_status_get_seq(wil, s));
	*mcast = wil_rx_status_get_mcast(s);
	*retry = wil_rx_status_get_retry(s);
}
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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ath10k_wmi_dbglog (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath10k_wmi_event_debug_mesg(struct ath10k *ar, struct sk_buff *skb)
{
	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi event debug mesg len %d\n",
		   skb->len);

	trace_ath10k_wmi_dbglog(ar, skb->data, skb->len);

	return 0;
}
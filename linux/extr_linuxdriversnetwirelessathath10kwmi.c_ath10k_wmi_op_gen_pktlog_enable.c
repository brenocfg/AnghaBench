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
typedef  int /*<<< orphan*/  u32 ;
struct wmi_pdev_pktlog_enable_cmd {int /*<<< orphan*/  ev_bitmap; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ATH10K_PKTLOG_ANY ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_pktlog_enable(struct ath10k *ar, u32 ev_bitmap)
{
	struct wmi_pdev_pktlog_enable_cmd *cmd;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ev_bitmap &= ATH10K_PKTLOG_ANY;

	cmd = (struct wmi_pdev_pktlog_enable_cmd *)skb->data;
	cmd->ev_bitmap = __cpu_to_le32(ev_bitmap);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi enable pktlog filter 0x%08x\n",
		   ev_bitmap);
	return skb;
}
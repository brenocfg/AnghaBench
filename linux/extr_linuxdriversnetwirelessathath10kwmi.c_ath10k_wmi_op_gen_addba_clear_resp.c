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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_addba_clear_resp_cmd {TYPE_1__ peer_macaddr; int /*<<< orphan*/  vdev_id; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_addba_clear_resp(struct ath10k *ar, u32 vdev_id,
				   const u8 *mac)
{
	struct wmi_addba_clear_resp_cmd *cmd;
	struct sk_buff *skb;

	if (!mac)
		return ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_addba_clear_resp_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, mac);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi addba clear resp vdev_id 0x%X mac_addr %pM\n",
		   vdev_id, mac);
	return skb;
}
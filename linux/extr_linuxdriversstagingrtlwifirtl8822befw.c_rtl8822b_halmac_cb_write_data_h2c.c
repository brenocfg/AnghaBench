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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rtl_priv {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int /*<<< orphan*/  H2C_QUEUE ; 
 struct sk_buff* __netdev_alloc_skb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int _rtl8822be_send_bcn_or_cmd_packet (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

bool rtl8822b_halmac_cb_write_data_h2c(struct rtl_priv *rtlpriv, u8 *buf,
				       u32 size)
{
	struct sk_buff *skb = NULL;

	/* without GFP_DMA, pci_map_single() may not work */
	skb = __netdev_alloc_skb(NULL, size, GFP_ATOMIC | GFP_DMA);
	memcpy((u8 *)skb_put(skb, size), buf, size);

	return _rtl8822be_send_bcn_or_cmd_packet(rtlpriv->hw, skb, H2C_QUEUE);
}
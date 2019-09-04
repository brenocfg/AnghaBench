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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct s_smc {TYPE_1__ os; } ;

/* Variables and functions */
 int FDDI_MAC_HDR_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fddi_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,char*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

int mac_drv_rx_init(struct s_smc *smc, int len, int fc,
		    char *look_ahead, int la_len)
{
	struct sk_buff *skb;

	pr_debug("entering mac_drv_rx_init(len=%d)\n", len);

	// "Received" a SMT or NSA frame of the local SMT.

	if (len != la_len || len < FDDI_MAC_HDR_LEN || !look_ahead) {
		pr_debug("fddi: Discard invalid local SMT frame\n");
		pr_debug("  len=%d, la_len=%d, (ULONG) look_ahead=%08lXh.\n",
		       len, la_len, (unsigned long) look_ahead);
		return 0;
	}
	skb = alloc_skb(len + 3, GFP_ATOMIC);
	if (!skb) {
		pr_debug("fddi: Local SMT: skb memory exhausted.\n");
		return 0;
	}
	skb_reserve(skb, 3);
	skb_put(skb, len);
	skb_copy_to_linear_data(skb, look_ahead, len);

	// deliver frame to system
	skb->protocol = fddi_type_trans(skb, smc->os.dev);
	netif_rx(skb);

	return 0;
}
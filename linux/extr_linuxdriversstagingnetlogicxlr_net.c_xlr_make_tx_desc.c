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
typedef  int u64 ;
struct sk_buff {scalar_t__ len; } ;
struct nlm_fmn_msg {int msg0; int msg1; scalar_t__ msg3; scalar_t__ msg2; } ;

/* Variables and functions */
 int XLR_FB_STN ; 
 int nlm_core_id () ; 
 unsigned long virt_to_phys (struct sk_buff*) ; 

__attribute__((used)) static void xlr_make_tx_desc(struct nlm_fmn_msg *msg, unsigned long addr,
			     struct sk_buff *skb)
{
	unsigned long physkb = virt_to_phys(skb);
	int cpu_core = nlm_core_id();
	int fr_stn_id = cpu_core * 8 + XLR_FB_STN;	/* FB to 6th bucket */

	msg->msg0 = (((u64)1 << 63)	|	/* End of packet descriptor */
		((u64)127 << 54)	|	/* No Free back */
		(u64)skb->len << 40	|	/* Length of data */
		((u64)addr));
	msg->msg1 = (((u64)1 << 63)	|
		((u64)fr_stn_id << 54)	|	/* Free back id */
		(u64)0 << 40		|	/* Set len to 0 */
		((u64)physkb  & 0xffffffff));	/* 32bit address */
	msg->msg2 = 0;
	msg->msg3 = 0;
}
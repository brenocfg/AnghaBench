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
struct tun_struct {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void tun_automq_xmit(struct tun_struct *tun, struct sk_buff *skb)
{
#ifdef CONFIG_RPS
	if (tun->numqueues == 1 && static_key_false(&rps_needed)) {
		/* Select queue was not called for the skbuff, so we extract the
		 * RPS hash and save it into the flow_table here.
		 */
		__u32 rxhash;

		rxhash = __skb_get_hash_symmetric(skb);
		if (rxhash) {
			struct tun_flow_entry *e;
			e = tun_flow_find(&tun->flows[tun_hashfn(rxhash)],
					rxhash);
			if (e)
				tun_flow_save_rps_rxhash(e, rxhash);
		}
	}
#endif
}
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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct j1939_sk_buff_cb {int dummy; } ;
struct j1939_priv {int dummy; } ;
typedef  int pgn_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int j1939_send_one (struct j1939_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  j1939_tp_im_involved (struct j1939_sk_buff_cb const*,int) ; 
 struct sk_buff* j1939_tp_tx_dat_new (struct j1939_priv*,struct j1939_sk_buff_cb const*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int j1939_xtp_do_tx_ctl(struct j1939_priv *priv,
			       const struct j1939_sk_buff_cb *re_skcb,
			       bool swap_src_dst, pgn_t pgn, const u8 *dat)
{
	struct sk_buff *skb;
	u8 *skdat;

	if (!j1939_tp_im_involved(re_skcb, swap_src_dst))
		return 0;

	skb = j1939_tp_tx_dat_new(priv, re_skcb, true, swap_src_dst);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	skdat = skb_put(skb, 8);
	memcpy(skdat, dat, 5);
	skdat[5] = (pgn >> 0);
	skdat[6] = (pgn >> 8);
	skdat[7] = (pgn >> 16);

	return j1939_send_one(priv, skb);
}
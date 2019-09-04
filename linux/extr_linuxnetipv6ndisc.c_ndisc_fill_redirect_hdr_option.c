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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_OPT_REDIRECT_HDR ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void ndisc_fill_redirect_hdr_option(struct sk_buff *skb,
					   struct sk_buff *orig_skb,
					   int rd_len)
{
	u8 *opt = skb_put(skb, rd_len);

	memset(opt, 0, 8);
	*(opt++) = ND_OPT_REDIRECT_HDR;
	*(opt++) = (rd_len >> 3);
	opt += 6;

	skb_copy_bits(orig_skb, skb_network_offset(orig_skb), opt,
		      rd_len - 8);
}
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
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LOWPAN_IPHC_TF_00 131 
#define  LOWPAN_IPHC_TF_01 130 
#define  LOWPAN_IPHC_TF_10 129 
#define  LOWPAN_IPHC_TF_11 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  lowpan_fetch_skb (struct sk_buff*,int*,int) ; 
 int /*<<< orphan*/  lowpan_iphc_tf_set_dscp (struct ipv6hdr*,int*) ; 
 int /*<<< orphan*/  lowpan_iphc_tf_set_ecn (struct ipv6hdr*,int*) ; 
 int /*<<< orphan*/  lowpan_iphc_tf_set_lbl (struct ipv6hdr*,int*) ; 

__attribute__((used)) static int lowpan_iphc_tf_decompress(struct sk_buff *skb, struct ipv6hdr *hdr,
				     u8 val)
{
	u8 tf[4];

	/* Traffic Class and Flow Label */
	switch (val) {
	case LOWPAN_IPHC_TF_00:
		/* ECN + DSCP + 4-bit Pad + Flow Label (4 bytes) */
		if (lowpan_fetch_skb(skb, tf, 4))
			return -EINVAL;

		/*                      1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 * |ECN|   DSCP    |  rsv  |             Flow Label                |
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 */
		lowpan_iphc_tf_set_ecn(hdr, tf);
		lowpan_iphc_tf_set_dscp(hdr, tf);
		lowpan_iphc_tf_set_lbl(hdr, &tf[1]);
		break;
	case LOWPAN_IPHC_TF_01:
		/* ECN + 2-bit Pad + Flow Label (3 bytes), DSCP is elided. */
		if (lowpan_fetch_skb(skb, tf, 3))
			return -EINVAL;

		/*                     1                   2
		 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 * |ECN|rsv|             Flow Label                |
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 */
		lowpan_iphc_tf_set_ecn(hdr, tf);
		lowpan_iphc_tf_set_lbl(hdr, &tf[0]);
		break;
	case LOWPAN_IPHC_TF_10:
		/* ECN + DSCP (1 byte), Flow Label is elided. */
		if (lowpan_fetch_skb(skb, tf, 1))
			return -EINVAL;

		/*  0 1 2 3 4 5 6 7
		 * +-+-+-+-+-+-+-+-+
		 * |ECN|   DSCP    |
		 * +-+-+-+-+-+-+-+-+
		 */
		lowpan_iphc_tf_set_ecn(hdr, tf);
		lowpan_iphc_tf_set_dscp(hdr, tf);
		break;
	case LOWPAN_IPHC_TF_11:
		/* Traffic Class and Flow Label are elided */
		break;
	default:
		WARN_ON_ONCE(1);
		return -EINVAL;
	}

	return 0;
}
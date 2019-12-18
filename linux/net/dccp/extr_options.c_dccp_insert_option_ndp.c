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
typedef  scalar_t__ u64 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {scalar_t__ dccps_ndp_count; } ;
struct TYPE_2__ {scalar_t__ dccpd_opt_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCPO_NDP_COUNT ; 
 scalar_t__ DCCP_MAX_OPT_LEN ; 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_encode_value_var (scalar_t__,unsigned char*,int const) ; 
 int dccp_ndp_len (scalar_t__) ; 
 scalar_t__ dccp_non_data_packet (struct sk_buff*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 unsigned char* skb_push (struct sk_buff*,int const) ; 

__attribute__((used)) static int dccp_insert_option_ndp(struct sock *sk, struct sk_buff *skb)
{
	struct dccp_sock *dp = dccp_sk(sk);
	u64 ndp = dp->dccps_ndp_count;

	if (dccp_non_data_packet(skb))
		++dp->dccps_ndp_count;
	else
		dp->dccps_ndp_count = 0;

	if (ndp > 0) {
		unsigned char *ptr;
		const int ndp_len = dccp_ndp_len(ndp);
		const int len = ndp_len + 2;

		if (DCCP_SKB_CB(skb)->dccpd_opt_len + len > DCCP_MAX_OPT_LEN)
			return -1;

		DCCP_SKB_CB(skb)->dccpd_opt_len += len;

		ptr = skb_push(skb, len);
		*ptr++ = DCCPO_NDP_COUNT;
		*ptr++ = len;
		dccp_encode_value_var(ndp, ptr, ndp_len);
	}

	return 0;
}
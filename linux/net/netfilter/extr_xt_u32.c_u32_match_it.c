#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct xt_u32_test {unsigned int nnums; unsigned int nvalues; TYPE_2__* value; TYPE_1__* location; } ;
struct xt_u32 {unsigned int ntests; struct xt_u32_test* tests; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int min; int max; } ;
struct TYPE_3__ {int number; int nextop; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  XT_U32_AND 131 
#define  XT_U32_AT 130 
#define  XT_U32_LEFTSH 129 
#define  XT_U32_RIGHTSH 128 
 int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_bits (struct sk_buff const*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool u32_match_it(const struct xt_u32 *data,
			 const struct sk_buff *skb)
{
	const struct xt_u32_test *ct;
	unsigned int testind;
	unsigned int nnums;
	unsigned int nvals;
	unsigned int i;
	__be32 n;
	u_int32_t pos;
	u_int32_t val;
	u_int32_t at;

	/*
	 * Small example: "0 >> 28 == 4 && 8 & 0xFF0000 >> 16 = 6, 17"
	 * (=IPv4 and (TCP or UDP)). Outer loop runs over the "&&" operands.
	 */
	for (testind = 0; testind < data->ntests; ++testind) {
		ct  = &data->tests[testind];
		at  = 0;
		pos = ct->location[0].number;

		if (skb->len < 4 || pos > skb->len - 4)
			return false;

		if (skb_copy_bits(skb, pos, &n, sizeof(n)) < 0)
			BUG();
		val   = ntohl(n);
		nnums = ct->nnums;

		/* Inner loop runs over "&", "<<", ">>" and "@" operands */
		for (i = 1; i < nnums; ++i) {
			u_int32_t number = ct->location[i].number;
			switch (ct->location[i].nextop) {
			case XT_U32_AND:
				val &= number;
				break;
			case XT_U32_LEFTSH:
				val <<= number;
				break;
			case XT_U32_RIGHTSH:
				val >>= number;
				break;
			case XT_U32_AT:
				if (at + val < at)
					return false;
				at += val;
				pos = number;
				if (at + 4 < at || skb->len < at + 4 ||
				    pos > skb->len - at - 4)
					return false;

				if (skb_copy_bits(skb, at + pos, &n,
						    sizeof(n)) < 0)
					BUG();
				val = ntohl(n);
				break;
			}
		}

		/* Run over the "," and ":" operands */
		nvals = ct->nvalues;
		for (i = 0; i < nvals; ++i)
			if (ct->value[i].min <= val && val <= ct->value[i].max)
				break;

		if (i >= ct->nvalues)
			return false;
	}

	return true;
}
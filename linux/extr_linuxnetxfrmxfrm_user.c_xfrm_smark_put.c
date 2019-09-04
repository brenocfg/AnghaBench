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
struct xfrm_mark {int v; int m; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRMA_SET_MARK ; 
 int /*<<< orphan*/  XFRMA_SET_MARK_MASK ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xfrm_smark_put(struct sk_buff *skb, struct xfrm_mark *m)
{
	int ret = 0;

	if (m->v | m->m) {
		ret = nla_put_u32(skb, XFRMA_SET_MARK, m->v);
		if (!ret)
			ret = nla_put_u32(skb, XFRMA_SET_MARK_MASK, m->m);
	}
	return ret;
}
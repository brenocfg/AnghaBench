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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  _u ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/ * __skb_header_pointer (struct sk_buff const*,int,int,void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be16 skb_flow_get_be16(const struct sk_buff *skb, int poff,
				void *data, int hlen)
{
	__be16 *u, _u;

	u = __skb_header_pointer(skb, poff, sizeof(_u), data, hlen, &_u);
	if (u)
		return *u;

	return 0;
}
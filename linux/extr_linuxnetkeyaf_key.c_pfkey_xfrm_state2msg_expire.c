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
struct xfrm_state {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __pfkey_xfrm_state2msg (struct xfrm_state const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct sk_buff *pfkey_xfrm_state2msg_expire(const struct xfrm_state *x,
							  int hsc)
{
	return __pfkey_xfrm_state2msg(x, 0, hsc);
}
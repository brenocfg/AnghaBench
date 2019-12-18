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
typedef  int u16 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/  cipso_v4_error (struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  cipso_v4_optptr (struct sk_buff*) ; 

void netlbl_skbuff_err(struct sk_buff *skb, u16 family, int error, int gateway)
{
	switch (family) {
	case AF_INET:
		if (cipso_v4_optptr(skb))
			cipso_v4_error(skb, error, gateway);
		break;
	}
}
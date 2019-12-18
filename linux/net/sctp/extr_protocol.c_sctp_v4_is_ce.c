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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tos; } ;

/* Variables and functions */
 int INET_ECN_is_ce (int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff const*) ; 

__attribute__((used)) static int sctp_v4_is_ce(const struct sk_buff *skb)
{
	return INET_ECN_is_ce(ip_hdr(skb)->tos);
}
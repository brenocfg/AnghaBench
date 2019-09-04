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
struct xt_action_param {int /*<<< orphan*/  matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int socket_match (struct sk_buff const*,struct xt_action_param*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
socket_mt4_v1_v2_v3(const struct sk_buff *skb, struct xt_action_param *par)
{
	return socket_match(skb, par, par->matchinfo);
}
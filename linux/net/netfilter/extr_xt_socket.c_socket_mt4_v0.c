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
struct xt_socket_mtinfo1 {int /*<<< orphan*/  flags; } ;
struct xt_action_param {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int socket_match (struct sk_buff const*,struct xt_action_param*,struct xt_socket_mtinfo1*) ; 

__attribute__((used)) static bool
socket_mt4_v0(const struct sk_buff *skb, struct xt_action_param *par)
{
	static struct xt_socket_mtinfo1 xt_info_v0 = {
		.flags = 0,
	};

	return socket_match(skb, par, &xt_info_v0);
}
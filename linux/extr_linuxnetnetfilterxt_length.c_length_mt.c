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
typedef  scalar_t__ u_int16_t ;
struct xt_length_info {scalar_t__ min; scalar_t__ max; int invert; } ;
struct xt_action_param {struct xt_length_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
 TYPE_1__* ip_hdr (struct sk_buff const*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
length_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_length_info *info = par->matchinfo;
	u_int16_t pktlen = ntohs(ip_hdr(skb)->tot_len);

	return (pktlen >= info->min && pktlen <= info->max) ^ info->invert;
}
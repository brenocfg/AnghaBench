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
 int /*<<< orphan*/  nf_osf_fingers ; 
 int nf_osf_match (struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_family (struct xt_action_param*) ; 
 int /*<<< orphan*/  xt_hooknum (struct xt_action_param*) ; 
 int /*<<< orphan*/  xt_in (struct xt_action_param*) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param*) ; 
 int /*<<< orphan*/  xt_out (struct xt_action_param*) ; 

__attribute__((used)) static bool
xt_osf_match_packet(const struct sk_buff *skb, struct xt_action_param *p)
{
	return nf_osf_match(skb, xt_family(p), xt_hooknum(p), xt_in(p),
			    xt_out(p), p->matchinfo, xt_net(p), nf_osf_fingers);
}
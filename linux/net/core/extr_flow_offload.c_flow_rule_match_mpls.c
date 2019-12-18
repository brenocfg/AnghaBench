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
struct flow_rule {int dummy; } ;
struct flow_match_mpls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_MPLS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_MATCH (struct flow_rule const*,int /*<<< orphan*/ ,struct flow_match_mpls*) ; 

void flow_rule_match_mpls(const struct flow_rule *rule,
			  struct flow_match_mpls *out)
{
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_MPLS, out);
}
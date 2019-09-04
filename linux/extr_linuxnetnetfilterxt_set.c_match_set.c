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
struct xt_action_param {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ip_set_adt_opt {int dummy; } ;
typedef  int /*<<< orphan*/  ip_set_id_t ;

/* Variables and functions */
 scalar_t__ ip_set_test (int /*<<< orphan*/ ,struct sk_buff const*,struct xt_action_param const*,struct ip_set_adt_opt*) ; 

__attribute__((used)) static inline int
match_set(ip_set_id_t index, const struct sk_buff *skb,
	  const struct xt_action_param *par,
	  struct ip_set_adt_opt *opt, int inv)
{
	if (ip_set_test(index, skb, par, opt))
		inv = !inv;
	return inv;
}
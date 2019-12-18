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
struct netlink_ext_ack {int dummy; } ;
struct net_bridge {int dummy; } ;
typedef  enum br_boolopt_id { ____Placeholder_br_boolopt_id } br_boolopt_id ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_NO_LL_LEARN ; 
#define  BR_BOOLOPT_NO_LL_LEARN 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  br_opt_toggle (struct net_bridge*,int /*<<< orphan*/ ,int) ; 

int br_boolopt_toggle(struct net_bridge *br, enum br_boolopt_id opt, bool on,
		      struct netlink_ext_ack *extack)
{
	switch (opt) {
	case BR_BOOLOPT_NO_LL_LEARN:
		br_opt_toggle(br, BROPT_NO_LL_LEARN, on);
		break;
	default:
		/* shouldn't be called with unsupported options */
		WARN_ON(1);
		break;
	}

	return 0;
}
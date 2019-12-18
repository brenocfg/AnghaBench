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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct stp_config_pdu {scalar_t__ flags; int /*<<< orphan*/ * forward_delay; int /*<<< orphan*/ * hello_time; int /*<<< orphan*/ * max_age; int /*<<< orphan*/ * msg_age; int /*<<< orphan*/ * port; int /*<<< orphan*/ * sender; int /*<<< orphan*/  root_cost; int /*<<< orphan*/ * root; } ;
struct ebt_stp_config_info {scalar_t__ flags; scalar_t__ root_priol; scalar_t__ root_priou; scalar_t__ root_costl; scalar_t__ root_costu; scalar_t__ sender_priol; scalar_t__ sender_priou; scalar_t__ portl; scalar_t__ portu; scalar_t__ msg_agel; scalar_t__ msg_ageu; scalar_t__ max_agel; scalar_t__ max_ageu; scalar_t__ hello_timel; scalar_t__ hello_timeu; scalar_t__ forward_delayl; scalar_t__ forward_delayu; int /*<<< orphan*/  sender_addrmsk; int /*<<< orphan*/  sender_addr; int /*<<< orphan*/  root_addrmsk; int /*<<< orphan*/  root_addr; } ;
struct ebt_stp_info {int bitmask; struct ebt_stp_config_info config; } ;

/* Variables and functions */
 int EBT_STP_FLAGS ; 
 int EBT_STP_FWDD ; 
 int EBT_STP_HELLOTIME ; 
 int EBT_STP_MAXAGE ; 
 int EBT_STP_MSGAGE ; 
 int EBT_STP_PORT ; 
 int EBT_STP_ROOTADDR ; 
 int EBT_STP_ROOTCOST ; 
 int EBT_STP_ROOTPRIO ; 
 int EBT_STP_SENDERADDR ; 
 int EBT_STP_SENDERPRIO ; 
 scalar_t__ NF_INVF (struct ebt_stp_info const*,int,int) ; 
 scalar_t__ NR16 (int /*<<< orphan*/ *) ; 
 scalar_t__ NR32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ebt_filter_config(const struct ebt_stp_info *info,
			      const struct stp_config_pdu *stpc)
{
	const struct ebt_stp_config_info *c;
	u16 v16;
	u32 v32;

	c = &info->config;
	if ((info->bitmask & EBT_STP_FLAGS) &&
	    NF_INVF(info, EBT_STP_FLAGS, c->flags != stpc->flags))
		return false;
	if (info->bitmask & EBT_STP_ROOTPRIO) {
		v16 = NR16(stpc->root);
		if (NF_INVF(info, EBT_STP_ROOTPRIO,
			    v16 < c->root_priol || v16 > c->root_priou))
			return false;
	}
	if (info->bitmask & EBT_STP_ROOTADDR) {
		if (NF_INVF(info, EBT_STP_ROOTADDR,
			    !ether_addr_equal_masked(&stpc->root[2],
						     c->root_addr,
						     c->root_addrmsk)))
			return false;
	}
	if (info->bitmask & EBT_STP_ROOTCOST) {
		v32 = NR32(stpc->root_cost);
		if (NF_INVF(info, EBT_STP_ROOTCOST,
			    v32 < c->root_costl || v32 > c->root_costu))
			return false;
	}
	if (info->bitmask & EBT_STP_SENDERPRIO) {
		v16 = NR16(stpc->sender);
		if (NF_INVF(info, EBT_STP_SENDERPRIO,
			    v16 < c->sender_priol || v16 > c->sender_priou))
			return false;
	}
	if (info->bitmask & EBT_STP_SENDERADDR) {
		if (NF_INVF(info, EBT_STP_SENDERADDR,
			    !ether_addr_equal_masked(&stpc->sender[2],
						     c->sender_addr,
						     c->sender_addrmsk)))
			return false;
	}
	if (info->bitmask & EBT_STP_PORT) {
		v16 = NR16(stpc->port);
		if (NF_INVF(info, EBT_STP_PORT,
			    v16 < c->portl || v16 > c->portu))
			return false;
	}
	if (info->bitmask & EBT_STP_MSGAGE) {
		v16 = NR16(stpc->msg_age);
		if (NF_INVF(info, EBT_STP_MSGAGE,
			    v16 < c->msg_agel || v16 > c->msg_ageu))
			return false;
	}
	if (info->bitmask & EBT_STP_MAXAGE) {
		v16 = NR16(stpc->max_age);
		if (NF_INVF(info, EBT_STP_MAXAGE,
			    v16 < c->max_agel || v16 > c->max_ageu))
			return false;
	}
	if (info->bitmask & EBT_STP_HELLOTIME) {
		v16 = NR16(stpc->hello_time);
		if (NF_INVF(info, EBT_STP_HELLOTIME,
			    v16 < c->hello_timel || v16 > c->hello_timeu))
			return false;
	}
	if (info->bitmask & EBT_STP_FWDD) {
		v16 = NR16(stpc->forward_delay);
		if (NF_INVF(info, EBT_STP_FWDD,
			    v16 < c->forward_delayl || v16 > c->forward_delayu))
			return false;
	}
	return true;
}
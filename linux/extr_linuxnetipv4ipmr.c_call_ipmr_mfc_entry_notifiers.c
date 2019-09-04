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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ipmr_seq; } ;
struct net {TYPE_1__ ipv4; } ;
struct mfc_cache {int /*<<< orphan*/  _c; } ;
typedef  enum fib_event_type { ____Placeholder_fib_event_type } fib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  RTNL_FAMILY_IPMR ; 
 int mr_call_mfc_notifiers (struct net*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int call_ipmr_mfc_entry_notifiers(struct net *net,
					 enum fib_event_type event_type,
					 struct mfc_cache *mfc, u32 tb_id)
{
	return mr_call_mfc_notifiers(net, RTNL_FAMILY_IPMR, event_type,
				     &mfc->_c, tb_id, &net->ipv4.ipmr_seq);
}
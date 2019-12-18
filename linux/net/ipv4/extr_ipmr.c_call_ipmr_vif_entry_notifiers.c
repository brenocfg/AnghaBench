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
typedef  int /*<<< orphan*/  vifi_t ;
typedef  int /*<<< orphan*/  u32 ;
struct vif_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipmr_seq; } ;
struct net {TYPE_1__ ipv4; } ;
typedef  enum fib_event_type { ____Placeholder_fib_event_type } fib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  RTNL_FAMILY_IPMR ; 
 int mr_call_vif_notifiers (struct net*,int /*<<< orphan*/ ,int,struct vif_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int call_ipmr_vif_entry_notifiers(struct net *net,
					 enum fib_event_type event_type,
					 struct vif_device *vif,
					 vifi_t vif_index, u32 tb_id)
{
	return mr_call_vif_notifiers(net, RTNL_FAMILY_IPMR, event_type,
				     vif, vif_index, tb_id,
				     &net->ipv4.ipmr_seq);
}
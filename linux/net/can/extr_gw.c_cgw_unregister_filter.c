#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  can_mask; int /*<<< orphan*/  can_id; } ;
struct TYPE_6__ {TYPE_2__ filter; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct cgw_job {TYPE_3__ ccgw; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_can_gw_rcv ; 
 int /*<<< orphan*/  can_rx_unregister (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cgw_job*) ; 

__attribute__((used)) static inline void cgw_unregister_filter(struct net *net, struct cgw_job *gwj)
{
	can_rx_unregister(net, gwj->src.dev, gwj->ccgw.filter.can_id,
			  gwj->ccgw.filter.can_mask, can_can_gw_rcv, gwj);
}
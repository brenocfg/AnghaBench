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
struct TYPE_2__ {scalar_t__ type; scalar_t__ id; } ;
struct xdp_rxq_info {scalar_t__ reg_state; TYPE_1__ mem; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 scalar_t__ REG_STATE_REGISTERED ; 
 scalar_t__ REG_STATE_UNREGISTERED ; 
 scalar_t__ REG_STATE_UNUSED ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg_mem_model (struct xdp_rxq_info*) ; 

void xdp_rxq_info_unreg(struct xdp_rxq_info *xdp_rxq)
{
	/* Simplify driver cleanup code paths, allow unreg "unused" */
	if (xdp_rxq->reg_state == REG_STATE_UNUSED)
		return;

	WARN(!(xdp_rxq->reg_state == REG_STATE_REGISTERED), "Driver BUG");

	xdp_rxq_info_unreg_mem_model(xdp_rxq);

	xdp_rxq->reg_state = REG_STATE_UNREGISTERED;
	xdp_rxq->dev = NULL;

	/* Reset mem info to defaults */
	xdp_rxq->mem.id = 0;
	xdp_rxq->mem.type = 0;
}
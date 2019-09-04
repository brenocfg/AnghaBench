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
struct sk_buff {int dummy; } ;
struct atm_vcc {int dummy; } ;
struct atm_qdisc_data {int /*<<< orphan*/  task; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* old_pop ) (struct atm_vcc*,struct sk_buff*) ;struct atm_qdisc_data* parent; } ;

/* Variables and functions */
 TYPE_1__* VCC2FLOW (struct atm_vcc*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct atm_vcc*,struct sk_buff*,struct atm_qdisc_data*) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sch_atm_pop(struct atm_vcc *vcc, struct sk_buff *skb)
{
	struct atm_qdisc_data *p = VCC2FLOW(vcc)->parent;

	pr_debug("sch_atm_pop(vcc %p,skb %p,[qdisc %p])\n", vcc, skb, p);
	VCC2FLOW(vcc)->old_pop(vcc, skb);
	tasklet_schedule(&p->task);
}
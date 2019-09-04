#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct dsa_switch {TYPE_2__ nb; TYPE_1__* dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  nh; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_switch_event ; 
 int raw_notifier_chain_register (int /*<<< orphan*/ *,TYPE_2__*) ; 

int dsa_switch_register_notifier(struct dsa_switch *ds)
{
	ds->nb.notifier_call = dsa_switch_event;

	return raw_notifier_chain_register(&ds->dst->nh, &ds->nb);
}
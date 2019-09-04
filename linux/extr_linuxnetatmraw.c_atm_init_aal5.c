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
struct atm_vcc {TYPE_2__* dev; int /*<<< orphan*/  send; int /*<<< orphan*/ * push_oam; int /*<<< orphan*/  pop; int /*<<< orphan*/  push; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  send; } ;

/* Variables and functions */
 int /*<<< orphan*/  atm_pop_raw ; 
 int /*<<< orphan*/  atm_push_raw ; 

int atm_init_aal5(struct atm_vcc *vcc)
{
	vcc->push = atm_push_raw;
	vcc->pop = atm_pop_raw;
	vcc->push_oam = NULL;
	vcc->send = vcc->dev->ops->send;
	return 0;
}
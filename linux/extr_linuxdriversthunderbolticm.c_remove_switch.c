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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct tb_switch {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * remote; } ;

/* Variables and functions */
 TYPE_2__* tb_port_at (int /*<<< orphan*/ ,struct tb_switch*) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_switch_remove (struct tb_switch*) ; 
 struct tb_switch* tb_to_switch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_switch(struct tb_switch *sw)
{
	struct tb_switch *parent_sw;

	parent_sw = tb_to_switch(sw->dev.parent);
	tb_port_at(tb_route(sw), parent_sw)->remote = NULL;
	tb_switch_remove(sw);
}
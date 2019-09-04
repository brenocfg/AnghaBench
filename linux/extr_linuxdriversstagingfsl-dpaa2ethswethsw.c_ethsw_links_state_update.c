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
struct TYPE_3__ {int num_ifs; } ;
struct ethsw_core {TYPE_2__** ports; TYPE_1__ sw_attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  port_carrier_state_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ethsw_links_state_update(struct ethsw_core *ethsw)
{
	int i;

	for (i = 0; i < ethsw->sw_attr.num_ifs; i++)
		port_carrier_state_sync(ethsw->ports[i]->netdev);
}
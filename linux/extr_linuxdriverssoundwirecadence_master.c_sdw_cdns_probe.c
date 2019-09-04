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
struct TYPE_2__ {int /*<<< orphan*/ * port_ops; } ;
struct sdw_cdns {TYPE_1__ bus; int /*<<< orphan*/  tx_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns_port_ops ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

int sdw_cdns_probe(struct sdw_cdns *cdns)
{
	init_completion(&cdns->tx_complete);
	cdns->bus.port_ops = &cdns_port_ops;

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sfp_bus {int /*<<< orphan*/ * netdev; int /*<<< orphan*/ * upstream; int /*<<< orphan*/ * upstream_ops; } ;

/* Variables and functions */

__attribute__((used)) static void sfp_upstream_clear(struct sfp_bus *bus)
{
	bus->upstream_ops = NULL;
	bus->upstream = NULL;
	bus->netdev = NULL;
}
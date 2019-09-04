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
struct via_aux_drv {int addr; int /*<<< orphan*/  get_preferred_mode; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  name; struct via_aux_bus* bus; } ;
struct via_aux_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  get_preferred_mode ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  query_edid (struct via_aux_drv*) ; 
 int /*<<< orphan*/  via_aux_add (struct via_aux_drv*) ; 

void via_aux_edid_probe(struct via_aux_bus *bus)
{
	struct via_aux_drv drv = {
		.bus	=	bus,
		.addr	=	0x50,
		.name	=	name,
		.cleanup	=	cleanup,
		.get_preferred_mode	=	get_preferred_mode};

	query_edid(&drv);

	/* as EDID devices can be connected/disconnected just add the driver */
	via_aux_add(&drv);
}
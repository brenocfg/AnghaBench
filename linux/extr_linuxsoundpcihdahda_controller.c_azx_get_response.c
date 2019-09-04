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
struct hdac_bus {int dummy; } ;
struct azx {scalar_t__ single_cmd; scalar_t__ disabled; } ;

/* Variables and functions */
 int azx_rirb_get_response (struct hdac_bus*,unsigned int,unsigned int*) ; 
 int azx_single_get_response (struct hdac_bus*,unsigned int,unsigned int*) ; 
 struct azx* bus_to_azx (struct hdac_bus*) ; 

__attribute__((used)) static int azx_get_response(struct hdac_bus *bus, unsigned int addr,
			    unsigned int *res)
{
	struct azx *chip = bus_to_azx(bus);

	if (chip->disabled)
		return 0;
	if (chip->single_cmd)
		return azx_single_get_response(bus, addr, res);
	else
		return azx_rirb_get_response(bus, addr, res);
}
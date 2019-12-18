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
struct scarlett2_ports {scalar_t__* num; } ;

/* Variables and functions */
 size_t SCARLETT2_PORT_IN ; 
 int SCARLETT2_PORT_TYPE_COUNT ; 

__attribute__((used)) static int scarlett2_count_mux_srcs(const struct scarlett2_ports *ports)
{
	int port_type, count = 0;

	for (port_type = 0;
	     port_type < SCARLETT2_PORT_TYPE_COUNT;
	     port_type++)
		count += ports[port_type].num[SCARLETT2_PORT_IN];

	return count;
}
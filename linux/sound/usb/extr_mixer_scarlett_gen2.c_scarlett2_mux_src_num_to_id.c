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
typedef  int u32 ;
struct scarlett2_ports {int* num; int id; } ;

/* Variables and functions */
 size_t SCARLETT2_PORT_IN ; 
 int SCARLETT2_PORT_TYPE_COUNT ; 

__attribute__((used)) static u32 scarlett2_mux_src_num_to_id(const struct scarlett2_ports *ports,
				       int num)
{
	int port_type;

	for (port_type = 0;
	     port_type < SCARLETT2_PORT_TYPE_COUNT;
	     port_type++) {
		if (num < ports[port_type].num[SCARLETT2_PORT_IN])
			return ports[port_type].id | num;
		num -= ports[port_type].num[SCARLETT2_PORT_IN];
	}

	/* Oops */
	return 0;
}
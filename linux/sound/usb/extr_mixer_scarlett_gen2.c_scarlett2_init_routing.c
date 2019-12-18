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
typedef  int /*<<< orphan*/  u8 ;
struct scarlett2_ports {int* num; } ;

/* Variables and functions */
 size_t SCARLETT2_PORT_IN ; 
 size_t SCARLETT2_PORT_OUT ; 
#define  SCARLETT2_PORT_TYPE_ADAT 130 
#define  SCARLETT2_PORT_TYPE_ANALOGUE 129 
 size_t SCARLETT2_PORT_TYPE_PCM ; 
#define  SCARLETT2_PORT_TYPE_SPDIF 128 
 int scarlett2_get_port_start_num (struct scarlett2_ports const*,size_t,int) ; 

__attribute__((used)) static void scarlett2_init_routing(u8 *mux,
				   const struct scarlett2_ports *ports)
{
	int i, input_num, input_count, port_type;
	int output_num, output_count, port_type_connect_num;

	static const int connect_order[] = {
		SCARLETT2_PORT_TYPE_ANALOGUE,
		SCARLETT2_PORT_TYPE_SPDIF,
		SCARLETT2_PORT_TYPE_ADAT,
		-1
	};

	/* Assign PCM inputs (routing outputs) */
	output_num = scarlett2_get_port_start_num(ports,
						  SCARLETT2_PORT_OUT,
						  SCARLETT2_PORT_TYPE_PCM);
	output_count = ports[SCARLETT2_PORT_TYPE_PCM].num[SCARLETT2_PORT_OUT];

	for (port_type = connect_order[port_type_connect_num = 0];
	     port_type >= 0;
	     port_type = connect_order[++port_type_connect_num]) {
		input_num = scarlett2_get_port_start_num(
			ports, SCARLETT2_PORT_IN, port_type);
		input_count = ports[port_type].num[SCARLETT2_PORT_IN];
		for (i = 0;
		     i < input_count && output_count;
		     i++, output_count--)
			mux[output_num++] = input_num++;
	}

	/* Assign PCM outputs (routing inputs) */
	input_num = scarlett2_get_port_start_num(ports,
						 SCARLETT2_PORT_IN,
						 SCARLETT2_PORT_TYPE_PCM);
	input_count = ports[SCARLETT2_PORT_TYPE_PCM].num[SCARLETT2_PORT_IN];

	for (port_type = connect_order[port_type_connect_num = 0];
	     port_type >= 0;
	     port_type = connect_order[++port_type_connect_num]) {
		output_num = scarlett2_get_port_start_num(
			ports, SCARLETT2_PORT_OUT, port_type);
		output_count = ports[port_type].num[SCARLETT2_PORT_OUT];
		for (i = 0;
		     i < output_count && input_count;
		     i++, input_count--)
			mux[output_num++] = input_num++;
	}
}
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

__attribute__((used)) static int scarlett2_get_port_start_num(const struct scarlett2_ports *ports,
					int direction, int port_type)
{
	int i, num = 0;

	for (i = 0; i < port_type; i++)
		num += ports[i].num[direction];

	return num;
}
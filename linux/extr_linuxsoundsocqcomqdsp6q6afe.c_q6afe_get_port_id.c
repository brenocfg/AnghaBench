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
struct TYPE_2__ {int port_id; } ;

/* Variables and functions */
 int AFE_PORT_MAX ; 
 int EINVAL ; 
 TYPE_1__* port_maps ; 

int q6afe_get_port_id(int index)
{
	if (index < 0 || index >= AFE_PORT_MAX)
		return -EINVAL;

	return port_maps[index].port_id;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u64 ;
struct TYPE_4__ {size_t max_port_number; } ;
struct tb_switch {TYPE_3__* ports; TYPE_1__ config; } ;
struct TYPE_6__ {TYPE_2__* remote; } ;
struct TYPE_5__ {struct tb_switch* sw; } ;

/* Variables and functions */
 size_t TB_ROUTE_SHIFT ; 
 scalar_t__ tb_is_upstream_port (TYPE_3__*) ; 

struct tb_switch *get_switch_at_route(struct tb_switch *sw, u64 route)
{
	u8 next_port = route; /*
			       * Routes use a stride of 8 bits,
			       * eventhough a port index has 6 bits at most.
			       * */
	if (route == 0)
		return sw;
	if (next_port > sw->config.max_port_number)
		return NULL;
	if (tb_is_upstream_port(&sw->ports[next_port]))
		return NULL;
	if (!sw->ports[next_port].remote)
		return NULL;
	return get_switch_at_route(sw->ports[next_port].remote->sw,
				   route >> TB_ROUTE_SHIFT);
}
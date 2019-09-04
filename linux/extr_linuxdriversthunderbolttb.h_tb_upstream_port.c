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
struct TYPE_2__ {size_t upstream_port_number; } ;
struct tb_switch {TYPE_1__ config; struct tb_port* ports; } ;
struct tb_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct tb_port *tb_upstream_port(struct tb_switch *sw)
{
	return &sw->ports[sw->config.upstream_port_number];
}
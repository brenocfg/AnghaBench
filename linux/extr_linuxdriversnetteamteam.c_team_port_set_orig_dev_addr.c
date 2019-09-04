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
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;
struct team_port {TYPE_1__ orig; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __set_port_dev_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int team_port_set_orig_dev_addr(struct team_port *port)
{
	return __set_port_dev_addr(port->dev, port->orig.dev_addr);
}
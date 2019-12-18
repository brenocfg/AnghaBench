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
struct switch_val {int port_vlan; } ;
struct switch_dev {int /*<<< orphan*/  port_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  show_attrs (struct switch_dev*,int /*<<< orphan*/ ,struct switch_val*) ; 

__attribute__((used)) static void
show_port(struct switch_dev *dev, int port)
{
	struct switch_val val;

	printf("Port %d:\n", port);
	val.port_vlan = port;
	show_attrs(dev, dev->port_ops, &val);
}
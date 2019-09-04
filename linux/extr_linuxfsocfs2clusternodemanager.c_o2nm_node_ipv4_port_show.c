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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  nd_ipv4_port; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_o2nm_node (struct config_item*) ; 

__attribute__((used)) static ssize_t o2nm_node_ipv4_port_show(struct config_item *item, char *page)
{
	return sprintf(page, "%u\n", ntohs(to_o2nm_node(item)->nd_ipv4_port));
}
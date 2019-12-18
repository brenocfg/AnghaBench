#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t node_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  header; } ;

/* Variables and functions */
 TYPE_2__ c2c ; 
 TYPE_1__ dim_node ; 
 int /*<<< orphan*/ * header_node ; 

__attribute__((used)) static void setup_nodes_header(void)
{
	dim_node.header = header_node[c2c.node_info];
}
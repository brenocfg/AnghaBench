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
typedef  struct fwnode_handle const fwnode_handle ;

/* Variables and functions */
 struct fwnode_handle const* of_fwnode_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_graph_get_next_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_of_node (struct fwnode_handle const*) ; 

__attribute__((used)) static struct fwnode_handle *
of_fwnode_graph_get_next_endpoint(const struct fwnode_handle *fwnode,
				  struct fwnode_handle *prev)
{
	return of_fwnode_handle(of_graph_get_next_endpoint(to_of_node(fwnode),
							   to_of_node(prev)));
}
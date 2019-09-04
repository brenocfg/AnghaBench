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
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 struct fwnode_handle* of_fwnode_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_of_node (struct fwnode_handle const*) ; 

__attribute__((used)) static struct fwnode_handle *
of_fwnode_get_parent(const struct fwnode_handle *fwnode)
{
	return of_fwnode_handle(of_get_parent(to_of_node(fwnode)));
}
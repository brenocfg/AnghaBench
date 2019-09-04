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
 int of_device_is_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_of_node (struct fwnode_handle const*) ; 

__attribute__((used)) static bool of_fwnode_device_is_available(const struct fwnode_handle *fwnode)
{
	return of_device_is_available(to_of_node(fwnode));
}
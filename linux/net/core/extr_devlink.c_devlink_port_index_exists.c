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
struct devlink {int dummy; } ;

/* Variables and functions */
 int devlink_port_get_by_index (struct devlink*,unsigned int) ; 

__attribute__((used)) static bool devlink_port_index_exists(struct devlink *devlink,
				      unsigned int port_index)
{
	return devlink_port_get_by_index(devlink, port_index);
}
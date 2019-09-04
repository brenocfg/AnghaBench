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
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; } ;

/* Variables and functions */
 scalar_t__ V4L2_MBUS_CSI2 ; 

__attribute__((used)) static inline bool is_parallel_bus(struct v4l2_fwnode_endpoint *ep)
{
	return ep->bus_type != V4L2_MBUS_CSI2;
}
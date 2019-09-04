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
struct vfio_ccw_private {int dummy; } ;
typedef  enum vfio_ccw_event { ____Placeholder_vfio_ccw_event } vfio_ccw_event ;

/* Variables and functions */

__attribute__((used)) static void fsm_nop(struct vfio_ccw_private *private,
		    enum vfio_ccw_event event)
{
}
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
struct vfio_ccw_private {TYPE_1__* sch; } ;
struct subchannel_id {int dummy; } ;
struct TYPE_2__ {struct subchannel_id schid; } ;

/* Variables and functions */

inline struct subchannel_id get_schid(struct vfio_ccw_private *p)
{
	return p->sch->schid;
}
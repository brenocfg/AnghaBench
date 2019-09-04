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
typedef  int /*<<< orphan*/  u64 ;
struct ccw_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct ccw_device*,int) ;} ;

/* Variables and functions */
 TYPE_1__* cmbops ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*,int) ; 

u64 cmf_read(struct ccw_device *cdev, int index)
{
	return cmbops->read(cdev, index);
}
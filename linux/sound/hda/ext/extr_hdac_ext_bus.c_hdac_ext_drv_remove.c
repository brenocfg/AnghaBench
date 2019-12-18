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
struct device {int dummy; } ;
struct TYPE_2__ {int (* remove ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  get_hdev (struct device*) ; 
 TYPE_1__* get_hdrv (struct device*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdac_ext_drv_remove(struct device *dev)
{
	return (get_hdrv(dev))->remove(get_hdev(dev));
}
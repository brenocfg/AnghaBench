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
struct TYPE_2__ {int /*<<< orphan*/  (* iucv_unregister ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  af_iucv_dev ; 
 int /*<<< orphan*/  af_iucv_driver ; 
 int /*<<< orphan*/  af_iucv_handler ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__* pr_iucv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void afiucv_iucv_exit(void)
{
	device_unregister(af_iucv_dev);
	driver_unregister(&af_iucv_driver);
	pr_iucv->iucv_unregister(&af_iucv_handler, 0);
}
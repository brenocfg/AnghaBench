#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ buffer; } ;

/* Variables and functions */
 int MAXMINOR ; 
 int /*<<< orphan*/  MKDEV (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 TYPE_1__* sys_ser ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vmlogrdr_cdev ; 
 scalar_t__ vmlogrdr_major ; 
 int /*<<< orphan*/  vmlogrdr_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  vmlogrdr_unregister_driver () ; 

__attribute__((used)) static void vmlogrdr_cleanup(void)
{
        int i;

	if (vmlogrdr_cdev) {
		cdev_del(vmlogrdr_cdev);
		vmlogrdr_cdev=NULL;
	}
	for (i=0; i < MAXMINOR; ++i ) {
		vmlogrdr_unregister_device(&sys_ser[i]);
		free_page((unsigned long)sys_ser[i].buffer);
	}
	vmlogrdr_unregister_driver();
	if (vmlogrdr_major) {
		unregister_chrdev_region(MKDEV(vmlogrdr_major, 0), MAXMINOR);
		vmlogrdr_major=0;
	}
}
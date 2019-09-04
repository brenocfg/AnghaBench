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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  CXLFLASH_MAX_ADAPTERS ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxlflash_class ; 
 int /*<<< orphan*/  cxlflash_major ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxlflash_class_exit(void)
{
	dev_t devno = MKDEV(cxlflash_major, 0);

	class_destroy(cxlflash_class);
	unregister_chrdev_region(devno, CXLFLASH_MAX_ADAPTERS);
}
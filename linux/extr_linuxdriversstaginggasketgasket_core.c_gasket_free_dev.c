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
struct gasket_internal_desc {int /*<<< orphan*/  mutex; int /*<<< orphan*/ ** devs; } ;
struct gasket_dev {size_t dev_idx; int /*<<< orphan*/  dev; struct gasket_internal_desc* internal_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gasket_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gasket_free_dev(struct gasket_dev *gasket_dev)
{
	struct gasket_internal_desc *internal_desc = gasket_dev->internal_desc;

	mutex_lock(&internal_desc->mutex);
	internal_desc->devs[gasket_dev->dev_idx] = NULL;
	mutex_unlock(&internal_desc->mutex);
	put_device(gasket_dev->dev);
	kfree(gasket_dev);
}
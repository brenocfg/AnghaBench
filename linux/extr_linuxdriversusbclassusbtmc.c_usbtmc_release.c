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
struct usbtmc_file_data {TYPE_1__* data; int /*<<< orphan*/  file_elem; } ;
struct inode {int dummy; } ;
struct file {struct usbtmc_file_data* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  kref; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usbtmc_file_data*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbtmc_delete ; 

__attribute__((used)) static int usbtmc_release(struct inode *inode, struct file *file)
{
	struct usbtmc_file_data *file_data = file->private_data;

	/* prevent IO _AND_ usbtmc_interrupt */
	mutex_lock(&file_data->data->io_mutex);
	spin_lock_irq(&file_data->data->dev_lock);

	list_del(&file_data->file_elem);

	spin_unlock_irq(&file_data->data->dev_lock);
	mutex_unlock(&file_data->data->io_mutex);

	kref_put(&file_data->data->kref, usbtmc_delete);
	file_data->data = NULL;
	kfree(file_data);
	return 0;
}
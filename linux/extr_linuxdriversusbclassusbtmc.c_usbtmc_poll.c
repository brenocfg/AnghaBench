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
struct usbtmc_file_data {int /*<<< orphan*/  srq_asserted; struct usbtmc_device_data* data; } ;
struct usbtmc_device_data {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  waitq; scalar_t__ zombie; } ;
struct file {struct usbtmc_file_data* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLPRI ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t usbtmc_poll(struct file *file, poll_table *wait)
{
	struct usbtmc_file_data *file_data = file->private_data;
	struct usbtmc_device_data *data = file_data->data;
	__poll_t mask;

	mutex_lock(&data->io_mutex);

	if (data->zombie) {
		mask = EPOLLHUP | EPOLLERR;
		goto no_poll;
	}

	poll_wait(file, &data->waitq, wait);

	mask = (atomic_read(&file_data->srq_asserted)) ? EPOLLPRI : 0;

no_poll:
	mutex_unlock(&data->io_mutex);
	return mask;
}
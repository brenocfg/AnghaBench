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
struct usbtmc_file_data {TYPE_1__* data; } ;
struct file {struct usbtmc_file_data* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  fasync; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbtmc_fasync(int fd, struct file *file, int on)
{
	struct usbtmc_file_data *file_data = file->private_data;

	return fasync_helper(fd, file, on, &file_data->data->fasync);
}
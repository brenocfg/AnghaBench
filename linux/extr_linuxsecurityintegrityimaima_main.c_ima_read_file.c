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
struct file {int dummy; } ;
typedef  enum kernel_read_file_id { ____Placeholder_kernel_read_file_id } kernel_read_file_id ;

/* Variables and functions */

int ima_read_file(struct file *file, enum kernel_read_file_id read_id)
{
	/*
	 * READING_FIRMWARE_PREALLOC_BUFFER
	 *
	 * Do devices using pre-allocated memory run the risk of the
	 * firmware being accessible to the device prior to the completion
	 * of IMA's signature verification any more than when using two
	 * buffers?
	 */
	return 0;
}
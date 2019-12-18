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
struct fd {int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  enum kernel_read_file_id { ____Placeholder_kernel_read_file_id } kernel_read_file_id ;

/* Variables and functions */
 int EBADF ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int kernel_read_file (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int kernel_read_file_from_fd(int fd, void **buf, loff_t *size, loff_t max_size,
			     enum kernel_read_file_id id)
{
	struct fd f = fdget(fd);
	int ret = -EBADF;

	if (!f.file)
		goto out;

	ret = kernel_read_file(f.file, buf, size, max_size, id);
out:
	fdput(f);
	return ret;
}
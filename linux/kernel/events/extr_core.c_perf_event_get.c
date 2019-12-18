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
struct file {int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct file* fget (unsigned int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  perf_fops ; 

struct file *perf_event_get(unsigned int fd)
{
	struct file *file = fget(fd);
	if (!file)
		return ERR_PTR(-EBADF);

	if (file->f_op != &perf_fops) {
		fput(file);
		return ERR_PTR(-EBADF);
	}

	return file;
}
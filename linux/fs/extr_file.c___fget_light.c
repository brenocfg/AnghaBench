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
struct files_struct {int /*<<< orphan*/  count; } ;
struct file {int f_mode; } ;
typedef  int fmode_t ;
struct TYPE_2__ {struct files_struct* files; } ;

/* Variables and functions */
 unsigned long FDPUT_FPUT ; 
 struct file* __fcheck_files (struct files_struct*,unsigned int) ; 
 struct file* __fget (unsigned int,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long __fget_light(unsigned int fd, fmode_t mask)
{
	struct files_struct *files = current->files;
	struct file *file;

	if (atomic_read(&files->count) == 1) {
		file = __fcheck_files(files, fd);
		if (!file || unlikely(file->f_mode & mask))
			return 0;
		return (unsigned long)file;
	} else {
		file = __fget(fd, mask, 1);
		if (!file)
			return 0;
		return FDPUT_FPUT | (unsigned long)file;
	}
}
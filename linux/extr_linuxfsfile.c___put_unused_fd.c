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
struct files_struct {unsigned int next_fd; } ;
struct fdtable {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_open_fd (unsigned int,struct fdtable*) ; 
 struct fdtable* files_fdtable (struct files_struct*) ; 

__attribute__((used)) static void __put_unused_fd(struct files_struct *files, unsigned int fd)
{
	struct fdtable *fdt = files_fdtable(files);
	__clear_open_fd(fd, fdt);
	if (fd < files->next_fd)
		files->next_fd = fd;
}
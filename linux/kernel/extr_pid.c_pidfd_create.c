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
struct pid {int dummy; } ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_pid (struct pid*) ; 
 int /*<<< orphan*/  pidfd_fops ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 

__attribute__((used)) static int pidfd_create(struct pid *pid)
{
	int fd;

	fd = anon_inode_getfd("[pidfd]", &pidfd_fops, get_pid(pid),
			      O_RDWR | O_CLOEXEC);
	if (fd < 0)
		put_pid(pid);

	return fd;
}
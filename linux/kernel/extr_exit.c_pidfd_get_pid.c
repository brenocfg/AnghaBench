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
struct fd {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 struct pid* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct pid*) ; 
 struct fd fdget (unsigned int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  get_pid (struct pid*) ; 
 struct pid* pidfd_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pid *pidfd_get_pid(unsigned int fd)
{
	struct fd f;
	struct pid *pid;

	f = fdget(fd);
	if (!f.file)
		return ERR_PTR(-EBADF);

	pid = pidfd_pid(f.file);
	if (!IS_ERR(pid))
		get_pid(pid);

	fdput(f);
	return pid;
}
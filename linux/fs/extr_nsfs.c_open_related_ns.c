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
struct path {int dummy; } ;
typedef  void ns_common ;
typedef  void file ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PTR_ERR (void*) ; 
 void* __ns_get_path (struct path*,void*) ; 
 int /*<<< orphan*/  current_cred () ; 
 void* dentry_open (struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_install (int,void*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 

int open_related_ns(struct ns_common *ns,
		   struct ns_common *(*get_ns)(struct ns_common *ns))
{
	struct path path = {};
	struct file *f;
	void *err;
	int fd;

	fd = get_unused_fd_flags(O_CLOEXEC);
	if (fd < 0)
		return fd;

	do {
		struct ns_common *relative;

		relative = get_ns(ns);
		if (IS_ERR(relative)) {
			put_unused_fd(fd);
			return PTR_ERR(relative);
		}

		err = __ns_get_path(&path, relative);
	} while (err == ERR_PTR(-EAGAIN));

	if (IS_ERR(err)) {
		put_unused_fd(fd);
		return PTR_ERR(err);
	}

	f = dentry_open(&path, O_RDONLY, current_cred());
	path_put(&path);
	if (IS_ERR(f)) {
		put_unused_fd(fd);
		fd = PTR_ERR(f);
	} else
		fd_install(fd, f);

	return fd;
}
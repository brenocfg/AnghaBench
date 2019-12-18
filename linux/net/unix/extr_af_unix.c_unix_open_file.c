#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_ns; } ;
struct TYPE_3__ {struct path path; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int ENOENT ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  O_PATH ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct file* dentry_open (struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int /*<<< orphan*/  smp_load_acquire (int /*<<< orphan*/ *) ; 
 TYPE_2__* sock_net (struct sock*) ; 
 TYPE_1__* unix_sk (struct sock*) ; 

__attribute__((used)) static int unix_open_file(struct sock *sk)
{
	struct path path;
	struct file *f;
	int fd;

	if (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		return -EPERM;

	if (!smp_load_acquire(&unix_sk(sk)->addr))
		return -ENOENT;

	path = unix_sk(sk)->path;
	if (!path.dentry)
		return -ENOENT;

	path_get(&path);

	fd = get_unused_fd_flags(O_CLOEXEC);
	if (fd < 0)
		goto out;

	f = dentry_open(&path, O_PATH, current_cred());
	if (IS_ERR(f)) {
		put_unused_fd(fd);
		fd = PTR_ERR(f);
		goto out;
	}

	fd_install(fd, f);
out:
	path_put(&path);

	return fd;
}
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
struct socket {int dummy; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct scm_cookie {TYPE_1__ creds; int /*<<< orphan*/  pid; } ;
struct msghdr {int /*<<< orphan*/  msg_controllen; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_uid_gid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 int scm_send (struct socket*,struct msghdr*,struct scm_cookie*,int) ; 
 int /*<<< orphan*/  task_tgid (int /*<<< orphan*/ ) ; 
 scalar_t__ unix_passcred_enabled (struct socket*,struct sock const*) ; 

__attribute__((used)) static int maybe_init_creds(struct scm_cookie *scm,
			    struct socket *socket,
			    const struct sock *other)
{
	int err;
	struct msghdr msg = { .msg_controllen = 0 };

	err = scm_send(socket, &msg, scm, false);
	if (err)
		return err;

	if (unix_passcred_enabled(socket, other)) {
		scm->pid = get_pid(task_tgid(current));
		current_uid_gid(&scm->creds.uid, &scm->creds.gid);
	}
	return err;
}
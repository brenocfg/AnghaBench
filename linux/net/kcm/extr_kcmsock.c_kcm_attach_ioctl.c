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
struct socket {int /*<<< orphan*/  file; } ;
struct kcm_attach {int /*<<< orphan*/  bpf_fd; int /*<<< orphan*/  fd; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_SOCKET_FILTER ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int PTR_ERR (struct bpf_prog*) ; 
 struct bpf_prog* bpf_prog_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int kcm_attach (struct socket*,struct socket*,struct bpf_prog*) ; 
 struct socket* sockfd_lookup (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int kcm_attach_ioctl(struct socket *sock, struct kcm_attach *info)
{
	struct socket *csock;
	struct bpf_prog *prog;
	int err;

	csock = sockfd_lookup(info->fd, &err);
	if (!csock)
		return -ENOENT;

	prog = bpf_prog_get_type(info->bpf_fd, BPF_PROG_TYPE_SOCKET_FILTER);
	if (IS_ERR(prog)) {
		err = PTR_ERR(prog);
		goto out;
	}

	err = kcm_attach(sock, csock, prog);
	if (err) {
		bpf_prog_put(prog);
		goto out;
	}

	/* Keep reference on file also */

	return 0;
out:
	fput(csock->file);
	return err;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct sock {scalar_t__ sk_type; scalar_t__ sk_protocol; scalar_t__ sk_family; } ;
struct bpf_prog {scalar_t__ type; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ BPF_PROG_TYPE_SK_REUSEPORT ; 
 scalar_t__ BPF_PROG_TYPE_SOCKET_FILTER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int EPERM ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int PTR_ERR (struct bpf_prog*) ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_FILTER_LOCKED ; 
 scalar_t__ SOCK_STREAM ; 
 struct bpf_prog* bpf_prog_get_type (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 scalar_t__ bpf_prog_size (int /*<<< orphan*/ ) ; 
 int reuseport_attach_prog (struct sock*,struct bpf_prog*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl_optmem_max ; 

int sk_reuseport_attach_bpf(u32 ufd, struct sock *sk)
{
	struct bpf_prog *prog;
	int err;

	if (sock_flag(sk, SOCK_FILTER_LOCKED))
		return -EPERM;

	prog = bpf_prog_get_type(ufd, BPF_PROG_TYPE_SOCKET_FILTER);
	if (IS_ERR(prog) && PTR_ERR(prog) == -EINVAL)
		prog = bpf_prog_get_type(ufd, BPF_PROG_TYPE_SK_REUSEPORT);
	if (IS_ERR(prog))
		return PTR_ERR(prog);

	if (prog->type == BPF_PROG_TYPE_SK_REUSEPORT) {
		/* Like other non BPF_PROG_TYPE_SOCKET_FILTER
		 * bpf prog (e.g. sockmap).  It depends on the
		 * limitation imposed by bpf_prog_load().
		 * Hence, sysctl_optmem_max is not checked.
		 */
		if ((sk->sk_type != SOCK_STREAM &&
		     sk->sk_type != SOCK_DGRAM) ||
		    (sk->sk_protocol != IPPROTO_UDP &&
		     sk->sk_protocol != IPPROTO_TCP) ||
		    (sk->sk_family != AF_INET &&
		     sk->sk_family != AF_INET6)) {
			err = -ENOTSUPP;
			goto err_prog_put;
		}
	} else {
		/* BPF_PROG_TYPE_SOCKET_FILTER */
		if (bpf_prog_size(prog->len) > sysctl_optmem_max) {
			err = -ENOMEM;
			goto err_prog_put;
		}
	}

	err = reuseport_attach_prog(sk, prog);
err_prog_put:
	if (err)
		bpf_prog_put(prog);

	return err;
}
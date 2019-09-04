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
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct smap_psock {int /*<<< orphan*/  strp_enabled; int /*<<< orphan*/  state; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  bpf_tx_msg; int /*<<< orphan*/  bpf_parse; } ;
struct bpf_sock_progs {int /*<<< orphan*/  bpf_tx_msg; int /*<<< orphan*/  bpf_parse; int /*<<< orphan*/  bpf_verdict; } ;
struct bpf_prog {int /*<<< orphan*/  strp_enabled; int /*<<< orphan*/  state; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  bpf_tx_msg; int /*<<< orphan*/  bpf_parse; } ;
struct bpf_map {int /*<<< orphan*/  numa_node; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 scalar_t__ IS_ERR (struct smap_psock*) ; 
 int PTR_ERR (struct smap_psock*) ; 
 struct smap_psock* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMAP_TX_RUNNING ; 
 int /*<<< orphan*/  TCP_ULP_BPF ; 
 struct smap_psock* bpf_prog_inc_not_zero (struct smap_psock*) ; 
 int /*<<< orphan*/  bpf_prog_put (struct smap_psock*) ; 
 int /*<<< orphan*/  bpf_tcp_msg_add (struct smap_psock*,struct sock*,struct smap_psock*) ; 
 int /*<<< orphan*/  psock_is_smap_sk (struct sock*) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smap_init_progs (struct smap_psock*,struct smap_psock*,struct smap_psock*) ; 
 struct smap_psock* smap_init_psock (struct sock*,int /*<<< orphan*/ ) ; 
 int smap_init_sock (struct smap_psock*,struct sock*) ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 int /*<<< orphan*/  smap_release_sock (struct smap_psock*,struct sock*) ; 
 int /*<<< orphan*/  smap_start_sock (struct smap_psock*,struct sock*) ; 
 int tcp_set_ulp_id (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __sock_map_ctx_update_elem(struct bpf_map *map,
				      struct bpf_sock_progs *progs,
				      struct sock *sock,
				      void *key)
{
	struct bpf_prog *verdict, *parse, *tx_msg;
	struct smap_psock *psock;
	bool new = false;
	int err = 0;

	/* 1. If sock map has BPF programs those will be inherited by the
	 * sock being added. If the sock is already attached to BPF programs
	 * this results in an error.
	 */
	verdict = READ_ONCE(progs->bpf_verdict);
	parse = READ_ONCE(progs->bpf_parse);
	tx_msg = READ_ONCE(progs->bpf_tx_msg);

	if (parse && verdict) {
		/* bpf prog refcnt may be zero if a concurrent attach operation
		 * removes the program after the above READ_ONCE() but before
		 * we increment the refcnt. If this is the case abort with an
		 * error.
		 */
		verdict = bpf_prog_inc_not_zero(verdict);
		if (IS_ERR(verdict))
			return PTR_ERR(verdict);

		parse = bpf_prog_inc_not_zero(parse);
		if (IS_ERR(parse)) {
			bpf_prog_put(verdict);
			return PTR_ERR(parse);
		}
	}

	if (tx_msg) {
		tx_msg = bpf_prog_inc_not_zero(tx_msg);
		if (IS_ERR(tx_msg)) {
			if (parse && verdict) {
				bpf_prog_put(parse);
				bpf_prog_put(verdict);
			}
			return PTR_ERR(tx_msg);
		}
	}

	psock = smap_psock_sk(sock);

	/* 2. Do not allow inheriting programs if psock exists and has
	 * already inherited programs. This would create confusion on
	 * which parser/verdict program is running. If no psock exists
	 * create one. Inside sk_callback_lock to ensure concurrent create
	 * doesn't update user data.
	 */
	if (psock) {
		if (!psock_is_smap_sk(sock)) {
			err = -EBUSY;
			goto out_progs;
		}
		if (READ_ONCE(psock->bpf_parse) && parse) {
			err = -EBUSY;
			goto out_progs;
		}
		if (READ_ONCE(psock->bpf_tx_msg) && tx_msg) {
			err = -EBUSY;
			goto out_progs;
		}
		if (!refcount_inc_not_zero(&psock->refcnt)) {
			err = -EAGAIN;
			goto out_progs;
		}
	} else {
		psock = smap_init_psock(sock, map->numa_node);
		if (IS_ERR(psock)) {
			err = PTR_ERR(psock);
			goto out_progs;
		}

		set_bit(SMAP_TX_RUNNING, &psock->state);
		new = true;
	}

	/* 3. At this point we have a reference to a valid psock that is
	 * running. Attach any BPF programs needed.
	 */
	if (tx_msg)
		bpf_tcp_msg_add(psock, sock, tx_msg);
	if (new) {
		err = tcp_set_ulp_id(sock, TCP_ULP_BPF);
		if (err)
			goto out_free;
	}

	if (parse && verdict && !psock->strp_enabled) {
		err = smap_init_sock(psock, sock);
		if (err)
			goto out_free;
		smap_init_progs(psock, verdict, parse);
		write_lock_bh(&sock->sk_callback_lock);
		smap_start_sock(psock, sock);
		write_unlock_bh(&sock->sk_callback_lock);
	}

	return err;
out_free:
	smap_release_sock(psock, sock);
out_progs:
	if (parse && verdict) {
		bpf_prog_put(parse);
		bpf_prog_put(verdict);
	}
	if (tx_msg)
		bpf_prog_put(tx_msg);
	return err;
}
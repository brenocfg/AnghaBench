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
struct sock {int dummy; } ;
struct smap_psock {int /*<<< orphan*/  sk_redir; int /*<<< orphan*/  apply_bytes; int /*<<< orphan*/  bpf_tx_msg; } ;
struct sk_msg_buff {int /*<<< orphan*/  apply_bytes; struct sock* sk; } ;
struct bpf_prog {unsigned int (* bpf_func ) (struct sk_msg_buff*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  insnsi; } ;

/* Variables and functions */
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int SK_PASS ; 
 unsigned int __SK_DROP ; 
 unsigned int __SK_REDIRECT ; 
 int /*<<< orphan*/  bpf_compute_data_pointers_sg (struct sk_msg_buff*) ; 
 unsigned int bpf_map_msg_verdict (unsigned int,struct sk_msg_buff*) ; 
 int /*<<< orphan*/  do_msg_redirect_map (struct sk_msg_buff*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ ) ; 
 unsigned int stub1 (struct sk_msg_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int smap_do_tx_msg(struct sock *sk,
				   struct smap_psock *psock,
				   struct sk_msg_buff *md)
{
	struct bpf_prog *prog;
	unsigned int rc, _rc;

	preempt_disable();
	rcu_read_lock();

	/* If the policy was removed mid-send then default to 'accept' */
	prog = READ_ONCE(psock->bpf_tx_msg);
	if (unlikely(!prog)) {
		_rc = SK_PASS;
		goto verdict;
	}

	bpf_compute_data_pointers_sg(md);
	md->sk = sk;
	rc = (*prog->bpf_func)(md, prog->insnsi);
	psock->apply_bytes = md->apply_bytes;

	/* Moving return codes from UAPI namespace into internal namespace */
	_rc = bpf_map_msg_verdict(rc, md);

	/* The psock has a refcount on the sock but not on the map and because
	 * we need to drop rcu read lock here its possible the map could be
	 * removed between here and when we need it to execute the sock
	 * redirect. So do the map lookup now for future use.
	 */
	if (_rc == __SK_REDIRECT) {
		if (psock->sk_redir)
			sock_put(psock->sk_redir);
		psock->sk_redir = do_msg_redirect_map(md);
		if (!psock->sk_redir) {
			_rc = __SK_DROP;
			goto verdict;
		}
		sock_hold(psock->sk_redir);
	}
verdict:
	rcu_read_unlock();
	preempt_enable();

	return _rc;
}
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
struct sock {int dummy; } ;
struct smap_psock {int eval; int sg_size; int cork_bytes; int apply_bytes; int /*<<< orphan*/ * cork; struct sock* sk_redir; } ;
struct sk_msg_buff {size_t sg_start; size_t sg_end; int cork_bytes; TYPE_1__* sg_data; } ;
struct TYPE_2__ {scalar_t__ length; scalar_t__ page_link; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int __GFP_NOWARN ; 
#define  __SK_DROP 130 
 int __SK_NONE ; 
#define  __SK_PASS 129 
#define  __SK_REDIRECT 128 
 int /*<<< orphan*/  apply_bytes_dec (struct smap_psock*,int) ; 
 int /*<<< orphan*/  bpf_md_init (struct smap_psock*) ; 
 int bpf_tcp_push (struct sock*,int,struct sk_msg_buff*,int,int) ; 
 int bpf_tcp_sendmsg_do_redirect (struct sock*,int,struct sk_msg_buff*,int) ; 
 int /*<<< orphan*/  free_bytes_sg (struct sock*,int,struct sk_msg_buff*,int) ; 
 int free_start_sg (struct sock*,struct sk_msg_buff*,int) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int) ; 
 int /*<<< orphan*/  kfree (struct sk_msg_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sk_msg_buff*,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  return_mem_sg (struct sock*,int,struct sk_msg_buff*) ; 
 int smap_do_tx_msg (struct sock*,struct smap_psock*,struct sk_msg_buff*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int bpf_exec_tx_verdict(struct smap_psock *psock,
			       struct sk_msg_buff *m,
			       struct sock *sk,
			       int *copied, int flags)
{
	bool cork = false, enospc = (m->sg_start == m->sg_end);
	struct sock *redir;
	int err = 0;
	int send;

more_data:
	if (psock->eval == __SK_NONE)
		psock->eval = smap_do_tx_msg(sk, psock, m);

	if (m->cork_bytes &&
	    m->cork_bytes > psock->sg_size && !enospc) {
		psock->cork_bytes = m->cork_bytes - psock->sg_size;
		if (!psock->cork) {
			psock->cork = kcalloc(1,
					sizeof(struct sk_msg_buff),
					GFP_ATOMIC | __GFP_NOWARN);

			if (!psock->cork) {
				err = -ENOMEM;
				goto out_err;
			}
		}
		memcpy(psock->cork, m, sizeof(*m));
		goto out_err;
	}

	send = psock->sg_size;
	if (psock->apply_bytes && psock->apply_bytes < send)
		send = psock->apply_bytes;

	switch (psock->eval) {
	case __SK_PASS:
		err = bpf_tcp_push(sk, send, m, flags, true);
		if (unlikely(err)) {
			*copied -= free_start_sg(sk, m, true);
			break;
		}

		apply_bytes_dec(psock, send);
		psock->sg_size -= send;
		break;
	case __SK_REDIRECT:
		redir = psock->sk_redir;
		apply_bytes_dec(psock, send);

		if (psock->cork) {
			cork = true;
			psock->cork = NULL;
		}

		return_mem_sg(sk, send, m);
		release_sock(sk);

		err = bpf_tcp_sendmsg_do_redirect(redir, send, m, flags);
		lock_sock(sk);

		if (unlikely(err < 0)) {
			int free = free_start_sg(sk, m, false);

			psock->sg_size = 0;
			if (!cork)
				*copied -= free;
		} else {
			psock->sg_size -= send;
		}

		if (cork) {
			free_start_sg(sk, m, true);
			psock->sg_size = 0;
			kfree(m);
			m = NULL;
			err = 0;
		}
		break;
	case __SK_DROP:
	default:
		free_bytes_sg(sk, send, m, true);
		apply_bytes_dec(psock, send);
		*copied -= send;
		psock->sg_size -= send;
		err = -EACCES;
		break;
	}

	if (likely(!err)) {
		bpf_md_init(psock);
		if (m &&
		    m->sg_data[m->sg_start].page_link &&
		    m->sg_data[m->sg_start].length)
			goto more_data;
	}

out_err:
	return err;
}
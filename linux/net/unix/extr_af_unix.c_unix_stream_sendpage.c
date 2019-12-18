#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct sock {scalar_t__ sk_state; int sk_shutdown; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;TYPE_2__ sk_receive_queue; int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sk_buff {size_t len; size_t data_len; size_t truesize; } ;
struct scm_cookie {int dummy; } ;
struct page {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  iolock; } ;

/* Variables and functions */
 int EAGAIN ; 
 size_t ENOTCONN ; 
 size_t EOPNOTSUPP ; 
 int EPIPE ; 
 int ERESTARTSYS ; 
 int MSG_DONTWAIT ; 
 int MSG_NOSIGNAL ; 
 int MSG_OOB ; 
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int maybe_init_creds (struct scm_cookie*,struct socket*,struct sock*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_add (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scm_destroy (struct scm_cookie*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_append_pagefrags (struct sk_buff*,struct page*,int,size_t) ; 
 struct sk_buff* skb_peek_tail (TYPE_2__*) ; 
 struct sk_buff* sock_alloc_send_pskb (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct sock* unix_peer (struct sock*) ; 
 int unix_scm_to_skb (struct scm_cookie*,struct sk_buff*,int) ; 
 TYPE_1__* unix_sk (struct sock*) ; 
 int /*<<< orphan*/  unix_skb_scm_eq (struct sk_buff*,struct scm_cookie*) ; 
 int /*<<< orphan*/  unix_state_lock (struct sock*) ; 
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 

__attribute__((used)) static ssize_t unix_stream_sendpage(struct socket *socket, struct page *page,
				    int offset, size_t size, int flags)
{
	int err;
	bool send_sigpipe = false;
	bool init_scm = true;
	struct scm_cookie scm;
	struct sock *other, *sk = socket->sk;
	struct sk_buff *skb, *newskb = NULL, *tail = NULL;

	if (flags & MSG_OOB)
		return -EOPNOTSUPP;

	other = unix_peer(sk);
	if (!other || sk->sk_state != TCP_ESTABLISHED)
		return -ENOTCONN;

	if (false) {
alloc_skb:
		unix_state_unlock(other);
		mutex_unlock(&unix_sk(other)->iolock);
		newskb = sock_alloc_send_pskb(sk, 0, 0, flags & MSG_DONTWAIT,
					      &err, 0);
		if (!newskb)
			goto err;
	}

	/* we must acquire iolock as we modify already present
	 * skbs in the sk_receive_queue and mess with skb->len
	 */
	err = mutex_lock_interruptible(&unix_sk(other)->iolock);
	if (err) {
		err = flags & MSG_DONTWAIT ? -EAGAIN : -ERESTARTSYS;
		goto err;
	}

	if (sk->sk_shutdown & SEND_SHUTDOWN) {
		err = -EPIPE;
		send_sigpipe = true;
		goto err_unlock;
	}

	unix_state_lock(other);

	if (sock_flag(other, SOCK_DEAD) ||
	    other->sk_shutdown & RCV_SHUTDOWN) {
		err = -EPIPE;
		send_sigpipe = true;
		goto err_state_unlock;
	}

	if (init_scm) {
		err = maybe_init_creds(&scm, socket, other);
		if (err)
			goto err_state_unlock;
		init_scm = false;
	}

	skb = skb_peek_tail(&other->sk_receive_queue);
	if (tail && tail == skb) {
		skb = newskb;
	} else if (!skb || !unix_skb_scm_eq(skb, &scm)) {
		if (newskb) {
			skb = newskb;
		} else {
			tail = skb;
			goto alloc_skb;
		}
	} else if (newskb) {
		/* this is fast path, we don't necessarily need to
		 * call to kfree_skb even though with newskb == NULL
		 * this - does no harm
		 */
		consume_skb(newskb);
		newskb = NULL;
	}

	if (skb_append_pagefrags(skb, page, offset, size)) {
		tail = skb;
		goto alloc_skb;
	}

	skb->len += size;
	skb->data_len += size;
	skb->truesize += size;
	refcount_add(size, &sk->sk_wmem_alloc);

	if (newskb) {
		err = unix_scm_to_skb(&scm, skb, false);
		if (err)
			goto err_state_unlock;
		spin_lock(&other->sk_receive_queue.lock);
		__skb_queue_tail(&other->sk_receive_queue, newskb);
		spin_unlock(&other->sk_receive_queue.lock);
	}

	unix_state_unlock(other);
	mutex_unlock(&unix_sk(other)->iolock);

	other->sk_data_ready(other);
	scm_destroy(&scm);
	return size;

err_state_unlock:
	unix_state_unlock(other);
err_unlock:
	mutex_unlock(&unix_sk(other)->iolock);
err:
	kfree_skb(newskb);
	if (send_sigpipe && !(flags & MSG_NOSIGNAL))
		send_sig(SIGPIPE, current, 0);
	if (!init_scm)
		scm_destroy(&scm);
	return err;
}
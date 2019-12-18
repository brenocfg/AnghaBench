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
struct socket {struct sock* sk; } ;
struct sockaddr {int dummy; } ;
struct sock {int sk_state; struct l2tp_tunnel* sk_user_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/ * ops; struct sock* private; int /*<<< orphan*/  hdrlen; } ;
struct pppox_sock {TYPE_1__ chan; } ;
struct pppol2tp_session {int /*<<< orphan*/  sk_lock; int /*<<< orphan*/  sk; scalar_t__ __sk; } ;
struct l2tp_tunnel_cfg {int /*<<< orphan*/  debug; int /*<<< orphan*/  encap; } ;
struct l2tp_tunnel {scalar_t__ peer_tunnel_id; scalar_t__ pwtype; scalar_t__ session_id; scalar_t__ peer_session_id; int /*<<< orphan*/  name; int /*<<< orphan*/ * sock; } ;
struct l2tp_session_cfg {scalar_t__ pw_type; int /*<<< orphan*/  member_0; } ;
struct l2tp_session {scalar_t__ peer_tunnel_id; scalar_t__ pwtype; scalar_t__ session_id; scalar_t__ peer_session_id; int /*<<< orphan*/  name; int /*<<< orphan*/ * sock; } ;
struct l2tp_connect_info {scalar_t__ fd; scalar_t__ peer_tunnel_id; int /*<<< orphan*/  peer_session_id; int /*<<< orphan*/  session_id; int /*<<< orphan*/  tunnel_id; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int EALREADY ; 
 int EBADF ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int EPROTOTYPE ; 
 scalar_t__ IS_ERR (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  L2TP_ENCAPTYPE_UDP ; 
 int /*<<< orphan*/  L2TP_MSG_CONTROL ; 
 scalar_t__ L2TP_PWTYPE_PPP ; 
 int /*<<< orphan*/  PPPOL2TP_L2TP_HDR_SIZE_NOSEQ ; 
 int PPPOX_CONNECTED ; 
 int PTR_ERR (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  kfree (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  l2tp_info (struct l2tp_tunnel*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct l2tp_tunnel* l2tp_session_create (int,struct l2tp_tunnel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct l2tp_session_cfg*) ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  l2tp_session_delete (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  l2tp_session_inc_refcount (struct l2tp_tunnel*) ; 
 struct pppol2tp_session* l2tp_session_priv (struct l2tp_tunnel*) ; 
 int l2tp_session_register (struct l2tp_tunnel*,struct l2tp_tunnel*) ; 
 int l2tp_tunnel_create (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct l2tp_tunnel_cfg*,struct l2tp_tunnel**) ; 
 int /*<<< orphan*/  l2tp_tunnel_dec_refcount (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  l2tp_tunnel_delete (struct l2tp_tunnel*) ; 
 struct l2tp_tunnel* l2tp_tunnel_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct l2tp_tunnel* l2tp_tunnel_get_session (struct l2tp_tunnel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_tunnel_inc_refcount (struct l2tp_tunnel*) ; 
 int l2tp_tunnel_register (struct l2tp_tunnel*,int /*<<< orphan*/ ,struct l2tp_tunnel_cfg*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ppp_register_net_channel (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pppol2tp_chan_ops ; 
 int /*<<< orphan*/  pppol2tp_session_init (struct l2tp_tunnel*) ; 
 int pppol2tp_sockaddr_get_info (struct sockaddr*,int,struct l2tp_connect_info*) ; 
 int /*<<< orphan*/  pppol2tp_tunnel_mtu (struct l2tp_tunnel*) ; 
 struct pppox_sock* pppox_sk (struct sock*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct sock*) ; 
 scalar_t__ rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int pppol2tp_connect(struct socket *sock, struct sockaddr *uservaddr,
			    int sockaddr_len, int flags)
{
	struct sock *sk = sock->sk;
	struct pppox_sock *po = pppox_sk(sk);
	struct l2tp_session *session = NULL;
	struct l2tp_connect_info info;
	struct l2tp_tunnel *tunnel;
	struct pppol2tp_session *ps;
	struct l2tp_session_cfg cfg = { 0, };
	bool drop_refcnt = false;
	bool drop_tunnel = false;
	bool new_session = false;
	bool new_tunnel = false;
	int error;

	error = pppol2tp_sockaddr_get_info(uservaddr, sockaddr_len, &info);
	if (error < 0)
		return error;

	lock_sock(sk);

	/* Check for already bound sockets */
	error = -EBUSY;
	if (sk->sk_state & PPPOX_CONNECTED)
		goto end;

	/* We don't supporting rebinding anyway */
	error = -EALREADY;
	if (sk->sk_user_data)
		goto end; /* socket is already attached */

	/* Don't bind if tunnel_id is 0 */
	error = -EINVAL;
	if (!info.tunnel_id)
		goto end;

	tunnel = l2tp_tunnel_get(sock_net(sk), info.tunnel_id);
	if (tunnel)
		drop_tunnel = true;

	/* Special case: create tunnel context if session_id and
	 * peer_session_id is 0. Otherwise look up tunnel using supplied
	 * tunnel id.
	 */
	if (!info.session_id && !info.peer_session_id) {
		if (tunnel == NULL) {
			struct l2tp_tunnel_cfg tcfg = {
				.encap = L2TP_ENCAPTYPE_UDP,
				.debug = 0,
			};

			/* Prevent l2tp_tunnel_register() from trying to set up
			 * a kernel socket.
			 */
			if (info.fd < 0) {
				error = -EBADF;
				goto end;
			}

			error = l2tp_tunnel_create(sock_net(sk), info.fd,
						   info.version,
						   info.tunnel_id,
						   info.peer_tunnel_id, &tcfg,
						   &tunnel);
			if (error < 0)
				goto end;

			l2tp_tunnel_inc_refcount(tunnel);
			error = l2tp_tunnel_register(tunnel, sock_net(sk),
						     &tcfg);
			if (error < 0) {
				kfree(tunnel);
				goto end;
			}
			drop_tunnel = true;
			new_tunnel = true;
		}
	} else {
		/* Error if we can't find the tunnel */
		error = -ENOENT;
		if (tunnel == NULL)
			goto end;

		/* Error if socket is not prepped */
		if (tunnel->sock == NULL)
			goto end;
	}

	if (tunnel->peer_tunnel_id == 0)
		tunnel->peer_tunnel_id = info.peer_tunnel_id;

	session = l2tp_tunnel_get_session(tunnel, info.session_id);
	if (session) {
		drop_refcnt = true;

		if (session->pwtype != L2TP_PWTYPE_PPP) {
			error = -EPROTOTYPE;
			goto end;
		}

		ps = l2tp_session_priv(session);

		/* Using a pre-existing session is fine as long as it hasn't
		 * been connected yet.
		 */
		mutex_lock(&ps->sk_lock);
		if (rcu_dereference_protected(ps->sk,
					      lockdep_is_held(&ps->sk_lock)) ||
		    ps->__sk) {
			mutex_unlock(&ps->sk_lock);
			error = -EEXIST;
			goto end;
		}
	} else {
		cfg.pw_type = L2TP_PWTYPE_PPP;

		session = l2tp_session_create(sizeof(struct pppol2tp_session),
					      tunnel, info.session_id,
					      info.peer_session_id, &cfg);
		if (IS_ERR(session)) {
			error = PTR_ERR(session);
			goto end;
		}

		pppol2tp_session_init(session);
		ps = l2tp_session_priv(session);
		l2tp_session_inc_refcount(session);

		mutex_lock(&ps->sk_lock);
		error = l2tp_session_register(session, tunnel);
		if (error < 0) {
			mutex_unlock(&ps->sk_lock);
			kfree(session);
			goto end;
		}
		drop_refcnt = true;
		new_session = true;
	}

	/* Special case: if source & dest session_id == 0x0000, this
	 * socket is being created to manage the tunnel. Just set up
	 * the internal context for use by ioctl() and sockopt()
	 * handlers.
	 */
	if ((session->session_id == 0) &&
	    (session->peer_session_id == 0)) {
		error = 0;
		goto out_no_ppp;
	}

	/* The only header we need to worry about is the L2TP
	 * header. This size is different depending on whether
	 * sequence numbers are enabled for the data channel.
	 */
	po->chan.hdrlen = PPPOL2TP_L2TP_HDR_SIZE_NOSEQ;

	po->chan.private = sk;
	po->chan.ops	 = &pppol2tp_chan_ops;
	po->chan.mtu	 = pppol2tp_tunnel_mtu(tunnel);

	error = ppp_register_net_channel(sock_net(sk), &po->chan);
	if (error) {
		mutex_unlock(&ps->sk_lock);
		goto end;
	}

out_no_ppp:
	/* This is how we get the session context from the socket. */
	sk->sk_user_data = session;
	rcu_assign_pointer(ps->sk, sk);
	mutex_unlock(&ps->sk_lock);

	/* Keep the reference we've grabbed on the session: sk doesn't expect
	 * the session to disappear. pppol2tp_session_destruct() is responsible
	 * for dropping it.
	 */
	drop_refcnt = false;

	sk->sk_state = PPPOX_CONNECTED;
	l2tp_info(session, L2TP_MSG_CONTROL, "%s: created\n",
		  session->name);

end:
	if (error) {
		if (new_session)
			l2tp_session_delete(session);
		if (new_tunnel)
			l2tp_tunnel_delete(tunnel);
	}
	if (drop_refcnt)
		l2tp_session_dec_refcount(session);
	if (drop_tunnel)
		l2tp_tunnel_dec_refcount(tunnel);
	release_sock(sk);

	return error;
}
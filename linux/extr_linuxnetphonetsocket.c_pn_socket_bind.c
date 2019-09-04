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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct socket {struct sock* sk; } ;
struct sockaddr_pn {scalar_t__ spn_family; int /*<<< orphan*/  spn_resource; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; TYPE_1__* sk_prot; } ;
struct pn_sock {int /*<<< orphan*/  resource; int /*<<< orphan*/  sobject; } ;
struct TYPE_2__ {int (* bind ) (struct sock*,struct sockaddr*,int) ;int (* get_port ) (struct sock*,scalar_t__) ;int (* hash ) (struct sock*) ;} ;

/* Variables and functions */
 scalar_t__ AF_PHONET ; 
 int EADDRNOTAVAIL ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 scalar_t__ TCP_CLOSE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ phonet_address_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pn_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pn_object (scalar_t__,scalar_t__) ; 
 scalar_t__ pn_port (int /*<<< orphan*/ ) ; 
 struct pn_sock* pn_sk (struct sock*) ; 
 int /*<<< orphan*/  pn_sockaddr_get_object (struct sockaddr_pn*) ; 
 int /*<<< orphan*/  port_mutex ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_hashed (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int stub1 (struct sock*,struct sockaddr*,int) ; 
 int stub2 (struct sock*,scalar_t__) ; 
 int stub3 (struct sock*) ; 

__attribute__((used)) static int pn_socket_bind(struct socket *sock, struct sockaddr *addr, int len)
{
	struct sock *sk = sock->sk;
	struct pn_sock *pn = pn_sk(sk);
	struct sockaddr_pn *spn = (struct sockaddr_pn *)addr;
	int err;
	u16 handle;
	u8 saddr;

	if (sk->sk_prot->bind)
		return sk->sk_prot->bind(sk, addr, len);

	if (len < sizeof(struct sockaddr_pn))
		return -EINVAL;
	if (spn->spn_family != AF_PHONET)
		return -EAFNOSUPPORT;

	handle = pn_sockaddr_get_object((struct sockaddr_pn *)addr);
	saddr = pn_addr(handle);
	if (saddr && phonet_address_lookup(sock_net(sk), saddr))
		return -EADDRNOTAVAIL;

	lock_sock(sk);
	if (sk->sk_state != TCP_CLOSE || pn_port(pn->sobject)) {
		err = -EINVAL; /* attempt to rebind */
		goto out;
	}
	WARN_ON(sk_hashed(sk));
	mutex_lock(&port_mutex);
	err = sk->sk_prot->get_port(sk, pn_port(handle));
	if (err)
		goto out_port;

	/* get_port() sets the port, bind() sets the address if applicable */
	pn->sobject = pn_object(saddr, pn_port(pn->sobject));
	pn->resource = spn->spn_resource;

	/* Enable RX on the socket */
	err = sk->sk_prot->hash(sk);
out_port:
	mutex_unlock(&port_mutex);
out:
	release_sock(sk);
	return err;
}
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
struct socket {struct sock* sk; } ;
struct sockaddr_iucv {int /*<<< orphan*/  siucv_nodeid; int /*<<< orphan*/  siucv_addr; int /*<<< orphan*/  siucv_port; int /*<<< orphan*/  siucv_name; int /*<<< orphan*/  siucv_user_id; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct sock {int dummy; } ;
struct iucv_sock {int /*<<< orphan*/  src_name; int /*<<< orphan*/  src_user_id; int /*<<< orphan*/  dst_name; int /*<<< orphan*/  dst_user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IUCV ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iucv_sock_getname(struct socket *sock, struct sockaddr *addr,
			     int peer)
{
	struct sockaddr_iucv *siucv = (struct sockaddr_iucv *) addr;
	struct sock *sk = sock->sk;
	struct iucv_sock *iucv = iucv_sk(sk);

	addr->sa_family = AF_IUCV;

	if (peer) {
		memcpy(siucv->siucv_user_id, iucv->dst_user_id, 8);
		memcpy(siucv->siucv_name, iucv->dst_name, 8);
	} else {
		memcpy(siucv->siucv_user_id, iucv->src_user_id, 8);
		memcpy(siucv->siucv_name, iucv->src_name, 8);
	}
	memset(&siucv->siucv_port, 0, sizeof(siucv->siucv_port));
	memset(&siucv->siucv_addr, 0, sizeof(siucv->siucv_addr));
	memset(&siucv->siucv_nodeid, 0, sizeof(siucv->siucv_nodeid));

	return sizeof(struct sockaddr_iucv);
}
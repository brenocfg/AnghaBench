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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct pep_sock {int pipe_handle; int /*<<< orphan*/  init_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAD ; 
 int /*<<< orphan*/  PNS_PEP_CONNECT_REQ ; 
 int PN_PIPE_INVALID_HANDLE ; 
 int /*<<< orphan*/  TCP_SYN_SENT ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int pipe_handler_request (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pep_sock_connect(struct sock *sk, struct sockaddr *addr, int len)
{
	struct pep_sock *pn = pep_sk(sk);
	int err;
	u8 data[4] = { 0 /* sub-blocks */, PAD, PAD, PAD };

	if (pn->pipe_handle == PN_PIPE_INVALID_HANDLE)
		pn->pipe_handle = 1; /* anything but INVALID_HANDLE */

	err = pipe_handler_request(sk, PNS_PEP_CONNECT_REQ,
				pn->init_enable, data, 4);
	if (err) {
		pn->pipe_handle = PN_PIPE_INVALID_HANDLE;
		return err;
	}

	sk->sk_state = TCP_SYN_SENT;

	return 0;
}
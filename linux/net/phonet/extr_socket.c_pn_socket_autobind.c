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
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr_pn {int /*<<< orphan*/  spn_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_2__ {int /*<<< orphan*/  sobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PHONET ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct sockaddr_pn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pn_port (int /*<<< orphan*/ ) ; 
 TYPE_1__* pn_sk (int /*<<< orphan*/ ) ; 
 int pn_socket_bind (struct socket*,struct sockaddr*,int) ; 

__attribute__((used)) static int pn_socket_autobind(struct socket *sock)
{
	struct sockaddr_pn sa;
	int err;

	memset(&sa, 0, sizeof(sa));
	sa.spn_family = AF_PHONET;
	err = pn_socket_bind(sock, (struct sockaddr *)&sa,
				sizeof(struct sockaddr_pn));
	if (err != -EINVAL)
		return err;
	BUG_ON(!pn_port(pn_sk(sock->sk)->sobject));
	return 0; /* socket was already bound */
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; TYPE_1__* ops; int /*<<< orphan*/  type; } ;
struct sock {TYPE_2__* sk_prot_creator; } ;
struct file {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  mux; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENFILE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PF_KCM ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_kcm_sock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcm_proto ; 
 TYPE_3__* kcm_sk (struct sock*) ; 
 struct sock* sk_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct socket* sock_alloc () ; 
 struct file* sock_alloc_file (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

__attribute__((used)) static struct file *kcm_clone(struct socket *osock)
{
	struct socket *newsock;
	struct sock *newsk;

	newsock = sock_alloc();
	if (!newsock)
		return ERR_PTR(-ENFILE);

	newsock->type = osock->type;
	newsock->ops = osock->ops;

	__module_get(newsock->ops->owner);

	newsk = sk_alloc(sock_net(osock->sk), PF_KCM, GFP_KERNEL,
			 &kcm_proto, false);
	if (!newsk) {
		sock_release(newsock);
		return ERR_PTR(-ENOMEM);
	}
	sock_init_data(newsock, newsk);
	init_kcm_sock(kcm_sk(newsk), kcm_sk(osock->sk)->mux);

	return sock_alloc_file(newsock, 0, osock->sk->sk_prot_creator->name);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strparser {TYPE_1__* sk; } ;
struct socket {TYPE_2__* ops; } ;
struct TYPE_4__ {int (* peek_len ) (struct socket*) ;} ;
struct TYPE_3__ {struct socket* sk_socket; } ;

/* Variables and functions */
 int INT_MAX ; 
 int stub1 (struct socket*) ; 

__attribute__((used)) static inline int strp_peek_len(struct strparser *strp)
{
	if (strp->sk) {
		struct socket *sock = strp->sk->sk_socket;

		return sock->ops->peek_len(sock);
	}

	/* If we don't have an associated socket there's nothing to peek.
	 * Return int max to avoid stopping the strparser.
	 */

	return INT_MAX;
}
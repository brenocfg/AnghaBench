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
struct socket {int /*<<< orphan*/ * ops; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  PF_ATMPVC ; 
 struct net init_net ; 
 int /*<<< orphan*/  pvc_proto_ops ; 
 int vcc_create (struct net*,struct socket*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pvc_create(struct net *net, struct socket *sock, int protocol,
		      int kern)
{
	if (net != &init_net)
		return -EAFNOSUPPORT;

	sock->ops = &pvc_proto_ops;
	return vcc_create(net, sock, protocol, PF_ATMPVC, kern);
}
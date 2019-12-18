#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/ * ops; } ;
struct net {int dummy; } ;
struct TYPE_5__ {void* sas_family; } ;
struct TYPE_4__ {void* sas_family; } ;
struct TYPE_6__ {TYPE_2__ remote; TYPE_1__ local; } ;

/* Variables and functions */
 void* AF_ATMSVC ; 
 TYPE_3__* ATM_SD (struct socket*) ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_proto_ops ; 
 int vcc_create (struct net*,struct socket*,int,void*,int) ; 

__attribute__((used)) static int svc_create(struct net *net, struct socket *sock, int protocol,
		      int kern)
{
	int error;

	if (!net_eq(net, &init_net))
		return -EAFNOSUPPORT;

	sock->ops = &svc_proto_ops;
	error = vcc_create(net, sock, protocol, AF_ATMSVC, kern);
	if (error)
		return error;
	ATM_SD(sock)->local.sas_family = AF_ATMSVC;
	ATM_SD(sock)->remote.sas_family = AF_ATMSVC;
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_3__ {int (* create ) (struct net*,struct socket*,TYPE_1__*,int) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int NFC_SOCKPROTO_MAX ; 
 struct net init_net ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 TYPE_1__** proto_tab ; 
 int /*<<< orphan*/  proto_tab_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct net*,struct socket*,TYPE_1__*,int) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_sock_create(struct net *net, struct socket *sock, int proto,
			   int kern)
{
	int rc = -EPROTONOSUPPORT;

	if (net != &init_net)
		return -EAFNOSUPPORT;

	if (proto < 0 || proto >= NFC_SOCKPROTO_MAX)
		return -EINVAL;

	read_lock(&proto_tab_lock);
	if (proto_tab[proto] &&	try_module_get(proto_tab[proto]->owner)) {
		rc = proto_tab[proto]->create(net, sock, proto_tab[proto], kern);
		module_put(proto_tab[proto]->owner);
	}
	read_unlock(&proto_tab_lock);

	return rc;
}
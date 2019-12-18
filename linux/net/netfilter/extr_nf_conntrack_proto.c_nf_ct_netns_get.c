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
typedef  int u8 ;
struct net {int dummy; } ;

/* Variables and functions */
#define  NFPROTO_BRIDGE 129 
#define  NFPROTO_INET 128 
 int nf_ct_netns_do_get (struct net*,int const) ; 
 int nf_ct_netns_inet_get (struct net*) ; 
 int /*<<< orphan*/  nf_ct_netns_put (struct net*,int const) ; 

int nf_ct_netns_get(struct net *net, u8 nfproto)
{
	int err;

	switch (nfproto) {
	case NFPROTO_INET:
		err = nf_ct_netns_inet_get(net);
		break;
	case NFPROTO_BRIDGE:
		err = nf_ct_netns_do_get(net, NFPROTO_BRIDGE);
		if (err < 0)
			return err;

		err = nf_ct_netns_inet_get(net);
		if (err < 0) {
			nf_ct_netns_put(net, NFPROTO_BRIDGE);
			return err;
		}
		break;
	default:
		err = nf_ct_netns_do_get(net, nfproto);
		break;
	}
	return err;
}
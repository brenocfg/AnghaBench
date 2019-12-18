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
typedef  int uint8_t ;
struct net {int dummy; } ;

/* Variables and functions */
#define  NFPROTO_BRIDGE 129 
#define  NFPROTO_INET 128 
 int NFPROTO_IPV4 ; 
 int NFPROTO_IPV6 ; 
 int /*<<< orphan*/  nf_ct_netns_do_put (struct net*,int const) ; 

void nf_ct_netns_put(struct net *net, uint8_t nfproto)
{
	switch (nfproto) {
	case NFPROTO_BRIDGE:
		nf_ct_netns_do_put(net, NFPROTO_BRIDGE);
		/* fall through */
	case NFPROTO_INET:
		nf_ct_netns_do_put(net, NFPROTO_IPV4);
		nf_ct_netns_do_put(net, NFPROTO_IPV6);
		break;
	default:
		nf_ct_netns_do_put(net, nfproto);
		break;
	}
}
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
typedef  scalar_t__ uint8_t ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFPROTO_INET ; 
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 
 int /*<<< orphan*/  nf_ct_netns_do_put (struct net*,scalar_t__) ; 

void nf_ct_netns_put(struct net *net, uint8_t nfproto)
{
	if (nfproto == NFPROTO_INET) {
		nf_ct_netns_do_put(net, NFPROTO_IPV4);
		nf_ct_netns_do_put(net, NFPROTO_IPV6);
	} else {
		nf_ct_netns_do_put(net, nfproto);
	}
}
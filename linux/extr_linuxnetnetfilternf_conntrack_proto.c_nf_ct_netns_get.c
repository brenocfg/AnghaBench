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
typedef  scalar_t__ u8 ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFPROTO_INET ; 
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 
 int nf_ct_netns_do_get (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  nf_ct_netns_put (struct net*,scalar_t__) ; 

int nf_ct_netns_get(struct net *net, u8 nfproto)
{
	int err;

	if (nfproto == NFPROTO_INET) {
		err = nf_ct_netns_do_get(net, NFPROTO_IPV4);
		if (err < 0)
			goto err1;
		err = nf_ct_netns_do_get(net, NFPROTO_IPV6);
		if (err < 0)
			goto err2;
	} else {
		err = nf_ct_netns_do_get(net, nfproto);
		if (err < 0)
			goto err1;
	}
	return 0;

err2:
	nf_ct_netns_put(net, NFPROTO_IPV4);
err1:
	return err;
}
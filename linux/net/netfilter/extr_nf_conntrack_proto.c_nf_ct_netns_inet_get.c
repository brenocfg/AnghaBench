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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int nf_ct_netns_do_get (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_netns_put (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_ct_netns_inet_get(struct net *net)
{
	int err;

	err = nf_ct_netns_do_get(net, NFPROTO_IPV4);
	if (err < 0)
		goto err1;
	err = nf_ct_netns_do_get(net, NFPROTO_IPV6);
	if (err < 0)
		goto err2;

	return err;
err2:
	nf_ct_netns_put(net, NFPROTO_IPV4);
err1:
	return err;
}
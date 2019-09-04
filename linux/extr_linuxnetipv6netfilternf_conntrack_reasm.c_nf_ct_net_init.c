#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * f; int /*<<< orphan*/  timeout; int /*<<< orphan*/  low_thresh; int /*<<< orphan*/  high_thresh; } ;
struct TYPE_4__ {TYPE_2__ frags; } ;
struct net {TYPE_1__ nf_frag; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_FRAG_HIGH_THRESH ; 
 int /*<<< orphan*/  IPV6_FRAG_LOW_THRESH ; 
 int /*<<< orphan*/  IPV6_FRAG_TIMEOUT ; 
 int /*<<< orphan*/  inet_frags_exit_net (TYPE_2__*) ; 
 int inet_frags_init_net (TYPE_2__*) ; 
 int nf_ct_frag6_sysctl_register (struct net*) ; 
 int /*<<< orphan*/  nf_frags ; 

__attribute__((used)) static int nf_ct_net_init(struct net *net)
{
	int res;

	net->nf_frag.frags.high_thresh = IPV6_FRAG_HIGH_THRESH;
	net->nf_frag.frags.low_thresh = IPV6_FRAG_LOW_THRESH;
	net->nf_frag.frags.timeout = IPV6_FRAG_TIMEOUT;
	net->nf_frag.frags.f = &nf_frags;

	res = inet_frags_init_net(&net->nf_frag.frags);
	if (res < 0)
		return res;
	res = nf_ct_frag6_sysctl_register(net);
	if (res < 0)
		inet_frags_exit_net(&net->nf_frag.frags);
	return res;
}
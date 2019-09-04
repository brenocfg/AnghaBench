#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct frag_queue {int dummy; } ;
struct TYPE_4__ {int qsize; int /*<<< orphan*/  rhash_params; int /*<<< orphan*/  frags_cache_name; int /*<<< orphan*/  frag_expire; int /*<<< orphan*/ * destructor; int /*<<< orphan*/  constructor; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_frags_fini (TYPE_1__*) ; 
 int inet_frags_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ip6frag_init ; 
 int /*<<< orphan*/  nf_ct_frag6_expire ; 
 int /*<<< orphan*/  nf_ct_net_ops ; 
 TYPE_1__ nf_frags ; 
 int /*<<< orphan*/  nf_frags_cache_name ; 
 int /*<<< orphan*/  nfct_rhash_params ; 
 int register_pernet_subsys (int /*<<< orphan*/ *) ; 

int nf_ct_frag6_init(void)
{
	int ret = 0;

	nf_frags.constructor = ip6frag_init;
	nf_frags.destructor = NULL;
	nf_frags.qsize = sizeof(struct frag_queue);
	nf_frags.frag_expire = nf_ct_frag6_expire;
	nf_frags.frags_cache_name = nf_frags_cache_name;
	nf_frags.rhash_params = nfct_rhash_params;
	ret = inet_frags_init(&nf_frags);
	if (ret)
		goto out;
	ret = register_pernet_subsys(&nf_ct_net_ops);
	if (ret)
		inet_frags_fini(&nf_frags);

out:
	return ret;
}
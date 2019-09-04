#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nf_conntrack_zone {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  use; } ;
struct TYPE_3__ {int tmpl_padto; } ;
struct nf_conn {TYPE_2__ ct_general; int /*<<< orphan*/  ct_net; int /*<<< orphan*/  status; TYPE_1__ proto; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ ARCH_KMALLOC_MINALIGN ; 
 int /*<<< orphan*/  IPS_TEMPLATE ; 
 scalar_t__ NFCT_ALIGN (unsigned long) ; 
 scalar_t__ NFCT_INFOMASK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nf_conn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_zone_add (struct nf_conn*,struct nf_conntrack_zone const*) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 

struct nf_conn *nf_ct_tmpl_alloc(struct net *net,
				 const struct nf_conntrack_zone *zone,
				 gfp_t flags)
{
	struct nf_conn *tmpl, *p;

	if (ARCH_KMALLOC_MINALIGN <= NFCT_INFOMASK) {
		tmpl = kzalloc(sizeof(*tmpl) + NFCT_INFOMASK, flags);
		if (!tmpl)
			return NULL;

		p = tmpl;
		tmpl = (struct nf_conn *)NFCT_ALIGN((unsigned long)p);
		if (tmpl != p) {
			tmpl = (struct nf_conn *)NFCT_ALIGN((unsigned long)p);
			tmpl->proto.tmpl_padto = (char *)tmpl - (char *)p;
		}
	} else {
		tmpl = kzalloc(sizeof(*tmpl), flags);
		if (!tmpl)
			return NULL;
	}

	tmpl->status = IPS_TEMPLATE;
	write_pnet(&tmpl->ct_net, net);
	nf_ct_zone_add(tmpl, zone);
	atomic_set(&tmpl->ct_general.use, 0);

	return tmpl;
}
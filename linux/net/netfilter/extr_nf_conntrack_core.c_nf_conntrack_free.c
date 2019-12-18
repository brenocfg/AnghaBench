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
struct TYPE_3__ {int /*<<< orphan*/  use; } ;
struct nf_conn {TYPE_1__ ct_general; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct net {TYPE_2__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_conntrack_cachep ; 
 int /*<<< orphan*/  nf_ct_ext_destroy (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_ext_free (struct nf_conn*) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

void nf_conntrack_free(struct nf_conn *ct)
{
	struct net *net = nf_ct_net(ct);

	/* A freed object has refcnt == 0, that's
	 * the golden rule for SLAB_TYPESAFE_BY_RCU
	 */
	WARN_ON(atomic_read(&ct->ct_general.use) != 0);

	nf_ct_ext_destroy(ct);
	nf_ct_ext_free(ct);
	kmem_cache_free(nf_conntrack_cachep, ct);
	smp_mb__before_atomic();
	atomic_dec(&net->ct.count);
}
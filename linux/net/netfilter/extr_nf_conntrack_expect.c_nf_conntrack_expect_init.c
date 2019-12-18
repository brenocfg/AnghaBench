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
struct nf_conntrack_expect {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int nf_conntrack_htable_size ; 
 int /*<<< orphan*/  nf_ct_alloc_hashtable (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_expect_cachep ; 
 int /*<<< orphan*/  nf_ct_expect_hash ; 
 int nf_ct_expect_hsize ; 
 int nf_ct_expect_max ; 

int nf_conntrack_expect_init(void)
{
	if (!nf_ct_expect_hsize) {
		nf_ct_expect_hsize = nf_conntrack_htable_size / 256;
		if (!nf_ct_expect_hsize)
			nf_ct_expect_hsize = 1;
	}
	nf_ct_expect_max = nf_ct_expect_hsize * 4;
	nf_ct_expect_cachep = kmem_cache_create("nf_conntrack_expect",
				sizeof(struct nf_conntrack_expect),
				0, 0, NULL);
	if (!nf_ct_expect_cachep)
		return -ENOMEM;

	nf_ct_expect_hash = nf_ct_alloc_hashtable(&nf_ct_expect_hsize, 0);
	if (!nf_ct_expect_hash) {
		kmem_cache_destroy(nf_ct_expect_cachep);
		return -ENOMEM;
	}

	return 0;
}
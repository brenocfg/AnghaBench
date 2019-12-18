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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  helper_extend ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_alloc_hashtable (int*,int /*<<< orphan*/ ) ; 
 int nf_ct_extend_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_helper_hash ; 
 int nf_ct_helper_hsize ; 
 int /*<<< orphan*/  nf_ct_nat_helpers ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int nf_conntrack_helper_init(void)
{
	int ret;
	nf_ct_helper_hsize = 1; /* gets rounded up to use one page */
	nf_ct_helper_hash =
		nf_ct_alloc_hashtable(&nf_ct_helper_hsize, 0);
	if (!nf_ct_helper_hash)
		return -ENOMEM;

	ret = nf_ct_extend_register(&helper_extend);
	if (ret < 0) {
		pr_err("nf_ct_helper: Unable to register helper extension.\n");
		goto out_extend;
	}

	INIT_LIST_HEAD(&nf_ct_nat_helpers);
	return 0;
out_extend:
	kvfree(nf_ct_helper_hash);
	return ret;
}
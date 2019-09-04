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
typedef  int u32 ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int gnttab_alloc_grant_references (int,int /*<<< orphan*/ *) ; 
 int gnttab_claim_grant_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_grant_foreign_access_ref (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  xen_page_to_gfn (struct page*) ; 

__attribute__((used)) static int
dmabuf_imp_grant_foreign_access(struct page **pages, u32 *refs,
				int count, int domid)
{
	grant_ref_t priv_gref_head;
	int i, ret;

	ret = gnttab_alloc_grant_references(count, &priv_gref_head);
	if (ret < 0) {
		pr_debug("Cannot allocate grant references, ret %d\n", ret);
		return ret;
	}

	for (i = 0; i < count; i++) {
		int cur_ref;

		cur_ref = gnttab_claim_grant_reference(&priv_gref_head);
		if (cur_ref < 0) {
			ret = cur_ref;
			pr_debug("Cannot claim grant reference, ret %d\n", ret);
			goto out;
		}

		gnttab_grant_foreign_access_ref(cur_ref, domid,
						xen_page_to_gfn(pages[i]), 0);
		refs[i] = cur_ref;
	}

	return 0;

out:
	gnttab_free_grant_references(priv_gref_head);
	return ret;
}
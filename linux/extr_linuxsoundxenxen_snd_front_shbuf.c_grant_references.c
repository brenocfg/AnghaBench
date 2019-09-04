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
struct xenbus_device {int otherend_id; } ;
struct xen_snd_front_shbuf {int num_grefs; int* grefs; scalar_t__ buffer; scalar_t__ directory; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int XEN_PAGE_SIZE ; 
 int /*<<< orphan*/  fill_page_dir (struct xen_snd_front_shbuf*,int) ; 
 int gnttab_alloc_grant_references (int,int /*<<< orphan*/ *) ; 
 int gnttab_claim_grant_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_grant_foreign_access_ref (int,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 
 unsigned long xen_page_to_gfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int grant_references(struct xenbus_device *xb_dev,
			    struct xen_snd_front_shbuf *buf,
			    int num_pages_dir, int num_pages_buffer,
			    int num_grefs)
{
	grant_ref_t priv_gref_head;
	unsigned long frame;
	int ret, i, j, cur_ref;
	int otherend_id;

	ret = gnttab_alloc_grant_references(num_grefs, &priv_gref_head);
	if (ret)
		return ret;

	buf->num_grefs = num_grefs;
	otherend_id = xb_dev->otherend_id;
	j = 0;

	for (i = 0; i < num_pages_dir; i++) {
		cur_ref = gnttab_claim_grant_reference(&priv_gref_head);
		if (cur_ref < 0) {
			ret = cur_ref;
			goto fail;
		}

		frame = xen_page_to_gfn(virt_to_page(buf->directory +
						     XEN_PAGE_SIZE * i));
		gnttab_grant_foreign_access_ref(cur_ref, otherend_id, frame, 0);
		buf->grefs[j++] = cur_ref;
	}

	for (i = 0; i < num_pages_buffer; i++) {
		cur_ref = gnttab_claim_grant_reference(&priv_gref_head);
		if (cur_ref < 0) {
			ret = cur_ref;
			goto fail;
		}

		frame = xen_page_to_gfn(virt_to_page(buf->buffer +
						     XEN_PAGE_SIZE * i));
		gnttab_grant_foreign_access_ref(cur_ref, otherend_id, frame, 0);
		buf->grefs[j++] = cur_ref;
	}

	gnttab_free_grant_references(priv_gref_head);
	fill_page_dir(buf, num_pages_dir);
	return 0;

fail:
	gnttab_free_grant_references(priv_gref_head);
	return ret;
}
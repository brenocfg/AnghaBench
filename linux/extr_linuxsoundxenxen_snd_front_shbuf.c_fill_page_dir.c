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
struct xensnd_page_directory {int /*<<< orphan*/  gref; int /*<<< orphan*/  gref_dir_next_page; } ;
struct xen_snd_front_shbuf {unsigned char* directory; int num_grefs; int /*<<< orphan*/ * grefs; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRANT_INVALID_REF ; 
 int XENSND_NUM_GREFS_PER_PAGE ; 
 int /*<<< orphan*/  XEN_PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fill_page_dir(struct xen_snd_front_shbuf *buf,
			  int num_pages_dir)
{
	struct xensnd_page_directory *page_dir;
	unsigned char *ptr;
	int i, cur_gref, grefs_left, to_copy;

	ptr = buf->directory;
	grefs_left = buf->num_grefs - num_pages_dir;
	/*
	 * skip grant references at the beginning, they are for pages granted
	 * for the page directory itself
	 */
	cur_gref = num_pages_dir;
	for (i = 0; i < num_pages_dir; i++) {
		page_dir = (struct xensnd_page_directory *)ptr;
		if (grefs_left <= XENSND_NUM_GREFS_PER_PAGE) {
			to_copy = grefs_left;
			page_dir->gref_dir_next_page = GRANT_INVALID_REF;
		} else {
			to_copy = XENSND_NUM_GREFS_PER_PAGE;
			page_dir->gref_dir_next_page = buf->grefs[i + 1];
		}

		memcpy(&page_dir->gref, &buf->grefs[cur_gref],
		       to_copy * sizeof(grant_ref_t));

		ptr += XEN_PAGE_SIZE;
		grefs_left -= to_copy;
		cur_gref += to_copy;
	}
}
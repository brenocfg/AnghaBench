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
typedef  unsigned int u64 ;
struct page {int dummy; } ;
struct TYPE_4__ {unsigned int sb_bsize_shift; int /*<<< orphan*/  sb_bsize; } ;
struct address_space {int dummy; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_vfs; TYPE_2__ sd_sb; struct address_space sd_aspace; } ;
struct TYPE_3__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {TYPE_1__ gl_name; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;

/* Variables and functions */
 int FGP_ACCESSED ; 
 int FGP_LOCK ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* find_get_page_flags (struct address_space*,unsigned long,int) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 struct page* grab_cache_page (struct address_space*,unsigned long) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,unsigned int) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  yield () ; 

struct buffer_head *gfs2_getbuf(struct gfs2_glock *gl, u64 blkno, int create)
{
	struct address_space *mapping = gfs2_glock2aspace(gl);
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	struct page *page;
	struct buffer_head *bh;
	unsigned int shift;
	unsigned long index;
	unsigned int bufnum;

	if (mapping == NULL)
		mapping = &sdp->sd_aspace;

	shift = PAGE_SHIFT - sdp->sd_sb.sb_bsize_shift;
	index = blkno >> shift;             /* convert block to page */
	bufnum = blkno - (index << shift);  /* block buf index within page */

	if (create) {
		for (;;) {
			page = grab_cache_page(mapping, index);
			if (page)
				break;
			yield();
		}
	} else {
		page = find_get_page_flags(mapping, index,
						FGP_LOCK|FGP_ACCESSED);
		if (!page)
			return NULL;
	}

	if (!page_has_buffers(page))
		create_empty_buffers(page, sdp->sd_sb.sb_bsize, 0);

	/* Locate header for our buffer within our page */
	for (bh = page_buffers(page); bufnum--; bh = bh->b_this_page)
		/* Do nothing */;
	get_bh(bh);

	if (!buffer_mapped(bh))
		map_bh(bh, sdp->sd_vfs, blkno);

	unlock_page(page);
	put_page(page);

	return bh;
}
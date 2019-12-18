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
struct writeback_control {int dummy; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDF_FORCE_AIL_FLUSH ; 
 int /*<<< orphan*/  gfs2_get_block_noalloc ; 
 struct gfs2_sbd* gfs2_mapping2sbd (struct address_space*) ; 
 int mpage_writepages (struct address_space*,struct writeback_control*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_writepages(struct address_space *mapping,
			   struct writeback_control *wbc)
{
	struct gfs2_sbd *sdp = gfs2_mapping2sbd(mapping);
	int ret = mpage_writepages(mapping, wbc, gfs2_get_block_noalloc);

	/*
	 * Even if we didn't write any pages here, we might still be holding
	 * dirty pages in the ail. We forcibly flush the ail because we don't
	 * want balance_dirty_pages() to loop indefinitely trying to write out
	 * pages held in the ail that it can't find.
	 */
	if (ret == 0)
		set_bit(SDF_FORCE_AIL_FLUSH, &sdp->sd_flags);

	return ret;
}
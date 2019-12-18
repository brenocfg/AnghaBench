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
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_buffer_cached (struct ocfs2_caching_info*,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_io_lock (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_io_unlock (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_set_buffer_uptodate (struct ocfs2_caching_info*,struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

void ocfs2_set_new_buffer_uptodate(struct ocfs2_caching_info *ci,
				   struct buffer_head *bh)
{
	/* This should definitely *not* exist in our cache */
	BUG_ON(ocfs2_buffer_cached(ci, bh));

	set_buffer_uptodate(bh);

	ocfs2_metadata_cache_io_lock(ci);
	ocfs2_set_buffer_uptodate(ci, bh);
	ocfs2_metadata_cache_io_unlock(ci);
}
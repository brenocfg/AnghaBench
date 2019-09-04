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
struct gfs2_meta_header {int /*<<< orphan*/  mh_magic; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static void meta_prep_new(struct buffer_head *bh)
{
	struct gfs2_meta_header *mh = (struct gfs2_meta_header *)bh->b_data;

	lock_buffer(bh);
	clear_buffer_dirty(bh);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);

	mh->mh_magic = cpu_to_be32(GFS2_MAGIC);
}
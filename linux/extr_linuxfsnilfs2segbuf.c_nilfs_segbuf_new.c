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
struct super_block {int dummy; } ;
struct nilfs_segment_buffer {scalar_t__ sb_nbio; int /*<<< orphan*/  sb_err; int /*<<< orphan*/  sb_bio_event; int /*<<< orphan*/ * sb_super_root; int /*<<< orphan*/  sb_payload_buffers; int /*<<< orphan*/  sb_segsum_buffers; int /*<<< orphan*/  sb_list; struct super_block* sb_super; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct nilfs_segment_buffer* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_segbuf_cachep ; 
 scalar_t__ unlikely (int) ; 

struct nilfs_segment_buffer *nilfs_segbuf_new(struct super_block *sb)
{
	struct nilfs_segment_buffer *segbuf;

	segbuf = kmem_cache_alloc(nilfs_segbuf_cachep, GFP_NOFS);
	if (unlikely(!segbuf))
		return NULL;

	segbuf->sb_super = sb;
	INIT_LIST_HEAD(&segbuf->sb_list);
	INIT_LIST_HEAD(&segbuf->sb_segsum_buffers);
	INIT_LIST_HEAD(&segbuf->sb_payload_buffers);
	segbuf->sb_super_root = NULL;

	init_completion(&segbuf->sb_bio_event);
	atomic_set(&segbuf->sb_err, 0);
	segbuf->sb_nbio = 0;

	return segbuf;
}
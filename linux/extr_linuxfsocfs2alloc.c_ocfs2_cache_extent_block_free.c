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
struct ocfs2_extent_block {int /*<<< orphan*/  h_suballoc_bit; int /*<<< orphan*/  h_blkno; int /*<<< orphan*/  h_suballoc_loc; int /*<<< orphan*/  h_suballoc_slot; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int ocfs2_cache_block_dealloc (struct ocfs2_cached_dealloc_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_cache_extent_block_free(struct ocfs2_cached_dealloc_ctxt *ctxt,
					 struct ocfs2_extent_block *eb)
{
	return ocfs2_cache_block_dealloc(ctxt, EXTENT_ALLOC_SYSTEM_INODE,
					 le16_to_cpu(eb->h_suballoc_slot),
					 le64_to_cpu(eb->h_suballoc_loc),
					 le64_to_cpu(eb->h_blkno),
					 le16_to_cpu(eb->h_suballoc_bit));
}
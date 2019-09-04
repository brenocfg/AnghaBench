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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int __ocfs2_increase_refcount (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 

int ocfs2_increase_refcount(handle_t *handle,
			    struct ocfs2_caching_info *ci,
			    struct buffer_head *ref_root_bh,
			    u64 cpos, u32 len,
			    struct ocfs2_alloc_context *meta_ac,
			    struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	return __ocfs2_increase_refcount(handle, ci, ref_root_bh,
					 cpos, len, 1,
					 meta_ac, dealloc);
}
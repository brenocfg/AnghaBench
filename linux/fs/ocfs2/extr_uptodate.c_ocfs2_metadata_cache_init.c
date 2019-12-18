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
struct ocfs2_caching_operations {int dummy; } ;
struct ocfs2_caching_info {struct ocfs2_caching_operations const* ci_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_reset (struct ocfs2_caching_info*,int) ; 

void ocfs2_metadata_cache_init(struct ocfs2_caching_info *ci,
			       const struct ocfs2_caching_operations *ops)
{
	BUG_ON(!ops);

	ci->ci_ops = ops;
	ocfs2_metadata_cache_reset(ci, 1);
}
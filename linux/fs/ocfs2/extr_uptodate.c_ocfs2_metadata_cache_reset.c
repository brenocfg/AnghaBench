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
struct ocfs2_caching_info {scalar_t__ ci_last_trans; scalar_t__ ci_created_trans; scalar_t__ ci_num_cached; int /*<<< orphan*/  ci_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_CACHE_FL_INLINE ; 

__attribute__((used)) static void ocfs2_metadata_cache_reset(struct ocfs2_caching_info *ci,
				       int clear)
{
	ci->ci_flags |= OCFS2_CACHE_FL_INLINE;
	ci->ci_num_cached = 0;

	if (clear) {
		ci->ci_created_trans = 0;
		ci->ci_last_trans = 0;
	}
}
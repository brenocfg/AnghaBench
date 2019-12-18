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
struct ocfs2_caching_info {int ci_flags; scalar_t__ ci_num_cached; } ;

/* Variables and functions */
 int OCFS2_CACHE_FL_INLINE ; 
 scalar_t__ OCFS2_CACHE_INFO_MAX_ARRAY ; 

__attribute__((used)) static inline int ocfs2_insert_can_use_array(struct ocfs2_caching_info *ci)
{
	return (ci->ci_flags & OCFS2_CACHE_FL_INLINE) &&
		(ci->ci_num_cached < OCFS2_CACHE_INFO_MAX_ARRAY);
}
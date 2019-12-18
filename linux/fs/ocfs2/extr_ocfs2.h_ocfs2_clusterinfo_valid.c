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
struct ocfs2_super {int s_feature_incompat; } ;

/* Variables and functions */
 int OCFS2_FEATURE_INCOMPAT_CLUSTERINFO ; 
 int OCFS2_FEATURE_INCOMPAT_USERSPACE_STACK ; 

__attribute__((used)) static inline int ocfs2_clusterinfo_valid(struct ocfs2_super *osb)
{
	return (osb->s_feature_incompat &
		(OCFS2_FEATURE_INCOMPAT_USERSPACE_STACK |
		 OCFS2_FEATURE_INCOMPAT_CLUSTERINFO));
}
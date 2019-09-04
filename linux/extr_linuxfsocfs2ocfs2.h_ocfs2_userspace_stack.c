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
struct ocfs2_super {int /*<<< orphan*/  osb_cluster_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_CLASSIC_CLUSTER_STACK ; 
 int /*<<< orphan*/  OCFS2_STACK_LABEL_LEN ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_clusterinfo_valid (struct ocfs2_super*) ; 

__attribute__((used)) static inline int ocfs2_userspace_stack(struct ocfs2_super *osb)
{
	if (ocfs2_clusterinfo_valid(osb) &&
	    memcmp(osb->osb_cluster_stack, OCFS2_CLASSIC_CLUSTER_STACK,
		   OCFS2_STACK_LABEL_LEN))
		return 1;
	return 0;
}
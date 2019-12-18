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
struct ocfs2_super {int osb_stackflags; } ;

/* Variables and functions */
 int OCFS2_CLUSTER_O2CB_GLOBAL_HEARTBEAT ; 
 scalar_t__ ocfs2_o2cb_stack (struct ocfs2_super*) ; 

__attribute__((used)) static inline int ocfs2_cluster_o2cb_global_heartbeat(struct ocfs2_super *osb)
{
	return ocfs2_o2cb_stack(osb) &&
		(osb->osb_stackflags & OCFS2_CLUSTER_O2CB_GLOBAL_HEARTBEAT);
}
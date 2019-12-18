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
struct ocfs2_super {scalar_t__ local_alloc_state; } ;

/* Variables and functions */
 scalar_t__ OCFS2_LA_ENABLED ; 
 scalar_t__ OCFS2_LA_THROTTLED ; 

__attribute__((used)) static inline int ocfs2_la_state_enabled(struct ocfs2_super *osb)
{
	return (osb->local_alloc_state == OCFS2_LA_THROTTLED ||
		osb->local_alloc_state == OCFS2_LA_ENABLED);
}
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
struct ocfs2_super {int osb_flags; int /*<<< orphan*/  osb_lock; } ;

/* Variables and functions */
 int OCFS2_OSB_HARD_RO ; 
 int OCFS2_OSB_SOFT_RO ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ocfs2_set_ro_flag(struct ocfs2_super *osb,
				     int hard)
{
	spin_lock(&osb->osb_lock);
	osb->osb_flags &= ~(OCFS2_OSB_SOFT_RO|OCFS2_OSB_HARD_RO);
	if (hard)
		osb->osb_flags |= OCFS2_OSB_HARD_RO;
	else
		osb->osb_flags |= OCFS2_OSB_SOFT_RO;
	spin_unlock(&osb->osb_lock);
}
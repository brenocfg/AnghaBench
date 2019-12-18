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
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ocfs2_is_hard_readonly(struct ocfs2_super *osb)
{
	int ret;

	spin_lock(&osb->osb_lock);
	ret = osb->osb_flags & OCFS2_OSB_HARD_RO;
	spin_unlock(&osb->osb_lock);

	return ret;
}
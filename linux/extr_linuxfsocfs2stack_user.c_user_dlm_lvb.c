#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* sb_lvbptr; } ;
struct ocfs2_dlm_lksb {TYPE_1__ lksb_fsdlm; } ;
struct dlm_lksb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void *user_dlm_lvb(struct ocfs2_dlm_lksb *lksb)
{
	if (!lksb->lksb_fsdlm.sb_lvbptr)
		lksb->lksb_fsdlm.sb_lvbptr = (char *)lksb +
					     sizeof(struct dlm_lksb);
	return (void *)(lksb->lksb_fsdlm.sb_lvbptr);
}
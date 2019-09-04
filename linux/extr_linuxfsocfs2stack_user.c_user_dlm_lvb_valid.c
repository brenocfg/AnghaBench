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
struct TYPE_2__ {int sb_flags; } ;
struct ocfs2_dlm_lksb {TYPE_1__ lksb_fsdlm; } ;

/* Variables and functions */
 int DLM_SBF_VALNOTVALID ; 

__attribute__((used)) static int user_dlm_lvb_valid(struct ocfs2_dlm_lksb *lksb)
{
	int invalid = lksb->lksb_fsdlm.sb_flags & DLM_SBF_VALNOTVALID;

	return !invalid;
}
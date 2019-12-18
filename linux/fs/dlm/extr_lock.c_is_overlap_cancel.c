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
struct dlm_lkb {int lkb_flags; } ;

/* Variables and functions */
 int DLM_IFL_OVERLAP_CANCEL ; 

__attribute__((used)) static inline int is_overlap_cancel(struct dlm_lkb *lkb)
{
	return lkb->lkb_flags & DLM_IFL_OVERLAP_CANCEL;
}
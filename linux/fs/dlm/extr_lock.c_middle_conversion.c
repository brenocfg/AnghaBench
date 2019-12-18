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
struct dlm_lkb {scalar_t__ lkb_grmode; scalar_t__ lkb_rqmode; } ;

/* Variables and functions */
 scalar_t__ DLM_LOCK_CW ; 
 scalar_t__ DLM_LOCK_PR ; 

__attribute__((used)) static inline int middle_conversion(struct dlm_lkb *lkb)
{
	if ((lkb->lkb_grmode==DLM_LOCK_PR && lkb->lkb_rqmode==DLM_LOCK_CW) ||
	    (lkb->lkb_rqmode==DLM_LOCK_PR && lkb->lkb_grmode==DLM_LOCK_CW))
		return 1;
	return 0;
}
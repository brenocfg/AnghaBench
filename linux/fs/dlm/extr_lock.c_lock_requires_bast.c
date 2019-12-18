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
struct dlm_lkb {int lkb_grmode; int lkb_highbast; } ;

/* Variables and functions */
 int DLM_LOCK_EX ; 
 int DLM_LOCK_PR ; 
 int /*<<< orphan*/ ** __dlm_compat_matrix ; 

__attribute__((used)) static int lock_requires_bast(struct dlm_lkb *gr, int high, int cw)
{
	if (gr->lkb_grmode == DLM_LOCK_PR && cw) {
		if (gr->lkb_highbast < DLM_LOCK_EX)
			return 1;
		return 0;
	}

	if (gr->lkb_highbast < high &&
	    !__dlm_compat_matrix[gr->lkb_grmode+1][high+1])
		return 1;
	return 0;
}
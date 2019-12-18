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
struct dlm_lkb {scalar_t__ lkb_rqmode; scalar_t__ lkb_grmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  middle_conversion (struct dlm_lkb*) ; 

__attribute__((used)) static inline int down_conversion(struct dlm_lkb *lkb)
{
	return (!middle_conversion(lkb) && lkb->lkb_rqmode < lkb->lkb_grmode);
}
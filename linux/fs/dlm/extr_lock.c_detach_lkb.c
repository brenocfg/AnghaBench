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
struct dlm_lkb {int /*<<< orphan*/ * lkb_resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_rsb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void detach_lkb(struct dlm_lkb *lkb)
{
	if (lkb->lkb_resource) {
		put_rsb(lkb->lkb_resource);
		lkb->lkb_resource = NULL;
	}
}
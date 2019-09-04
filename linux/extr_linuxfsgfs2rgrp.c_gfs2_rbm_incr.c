#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gfs2_rbm {scalar_t__ offset; int bii; TYPE_1__* rgd; } ;
struct TYPE_4__ {scalar_t__ bi_blocks; } ;
struct TYPE_3__ {int rd_length; } ;

/* Variables and functions */
 TYPE_2__* rbm_bi (struct gfs2_rbm*) ; 

__attribute__((used)) static bool gfs2_rbm_incr(struct gfs2_rbm *rbm)
{
	if (rbm->offset + 1 < rbm_bi(rbm)->bi_blocks) { /* in the same bitmap */
		rbm->offset++;
		return false;
	}
	if (rbm->bii == rbm->rgd->rd_length - 1) /* at the last bitmap */
		return true;

	rbm->offset = 0;
	rbm->bii++;
	return false;
}
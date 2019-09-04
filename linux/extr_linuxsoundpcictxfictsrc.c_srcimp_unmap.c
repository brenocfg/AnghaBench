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
struct TYPE_3__ {int msr; } ;
struct srcimp {int mapped; int /*<<< orphan*/ * imappers; TYPE_2__* mgr; TYPE_1__ rsc; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* imap_delete ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int srcimp_unmap(struct srcimp *srcimp)
{
	int i;

	/* Program master and conjugate resources */
	for (i = 0; i < srcimp->rsc.msr; i++) {
		if (srcimp->mapped & (0x1 << i)) {
			srcimp->mgr->imap_delete(srcimp->mgr,
						 &srcimp->imappers[i]);
			srcimp->mapped &= ~(0x1 << i);
		}
	}

	return 0;
}
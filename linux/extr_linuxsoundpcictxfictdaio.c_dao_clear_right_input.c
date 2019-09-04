#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct imapper {int dummy; } ;
struct TYPE_6__ {size_t msr; } ;
struct TYPE_5__ {int msr; } ;
struct daio {TYPE_2__ rscl; TYPE_1__ rscr; } ;
struct dao {struct imapper** imappers; TYPE_3__* mgr; struct daio daio; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* imap_delete ) (TYPE_3__*,struct imapper*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct imapper*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct imapper*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,struct imapper*) ; 

__attribute__((used)) static int dao_clear_right_input(struct dao *dao)
{
	struct imapper *entry;
	struct daio *daio = &dao->daio;
	int i;

	if (!dao->imappers[daio->rscl.msr])
		return 0;

	entry = dao->imappers[daio->rscl.msr];
	dao->mgr->imap_delete(dao->mgr, entry);
	/* Program conjugate resources */
	for (i = 1; i < daio->rscr.msr; i++) {
		entry = dao->imappers[daio->rscl.msr + i];
		dao->mgr->imap_delete(dao->mgr, entry);
		dao->imappers[daio->rscl.msr + i] = NULL;
	}

	kfree(dao->imappers[daio->rscl.msr]);
	dao->imappers[daio->rscl.msr] = NULL;

	return 0;
}
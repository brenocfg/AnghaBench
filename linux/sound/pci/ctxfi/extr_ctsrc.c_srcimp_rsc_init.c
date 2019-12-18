#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;
struct srcimp_mgr {TYPE_1__ mgr; } ;
struct srcimp_desc {int /*<<< orphan*/  msr; } ;
struct TYPE_7__ {TYPE_3__* ops; } ;
struct srcimp {TYPE_2__ rsc; struct srcimp_mgr* mgr; int /*<<< orphan*/ * ops; int /*<<< orphan*/  imappers; int /*<<< orphan*/ * idx; } ;
struct imapper {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* master ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SRCIMP ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rsc_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsc_uninit (TYPE_2__*) ; 
 TYPE_3__ srcimp_basic_rsc_ops ; 
 int /*<<< orphan*/  srcimp_ops ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int srcimp_rsc_init(struct srcimp *srcimp,
			   const struct srcimp_desc *desc,
			   struct srcimp_mgr *mgr)
{
	int err;

	err = rsc_init(&srcimp->rsc, srcimp->idx[0],
		       SRCIMP, desc->msr, mgr->mgr.hw);
	if (err)
		return err;

	/* Reserve memory for imapper nodes */
	srcimp->imappers = kcalloc(desc->msr, sizeof(struct imapper),
				   GFP_KERNEL);
	if (!srcimp->imappers) {
		err = -ENOMEM;
		goto error1;
	}

	/* Set srcimp specific operations */
	srcimp->rsc.ops = &srcimp_basic_rsc_ops;
	srcimp->ops = &srcimp_ops;
	srcimp->mgr = mgr;

	srcimp->rsc.ops->master(&srcimp->rsc);

	return 0;

error1:
	rsc_uninit(&srcimp->rsc);
	return err;
}
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
struct dao_desc {int /*<<< orphan*/  passthru; int /*<<< orphan*/  msr; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct dao {TYPE_1__ daio; struct daio_mgr* mgr; } ;
struct daio_mgr {int dummy; } ;
struct daio_desc {int /*<<< orphan*/  passthru; int /*<<< orphan*/  msr; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int dao_rsc_init (struct dao*,struct daio_desc*,struct daio_mgr*) ; 
 int /*<<< orphan*/  dao_rsc_uninit (struct dao*) ; 

__attribute__((used)) static int dao_rsc_reinit(struct dao *dao, const struct dao_desc *desc)
{
	struct daio_mgr *mgr = dao->mgr;
	struct daio_desc dsc = {0};

	dsc.type = dao->daio.type;
	dsc.msr = desc->msr;
	dsc.passthru = desc->passthru;
	dao_rsc_uninit(dao);
	return dao_rsc_init(dao, &dsc, mgr);
}
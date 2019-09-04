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
struct TYPE_4__ {int /*<<< orphan*/  mba; scalar_t__ mbfc; int /*<<< orphan*/  csense; int /*<<< orphan*/  mp; int /*<<< orphan*/  mme; int /*<<< orphan*/  ena; int /*<<< orphan*/  isc; int /*<<< orphan*/  mbi; int /*<<< orphan*/  intparm; } ;
struct subchannel {TYPE_2__ config; } ;
struct TYPE_3__ {scalar_t__ mbfc; int /*<<< orphan*/  csense; int /*<<< orphan*/  mp; int /*<<< orphan*/  mme; int /*<<< orphan*/  ena; int /*<<< orphan*/  isc; int /*<<< orphan*/  mbi; int /*<<< orphan*/  intparm; } ;
struct schib {int /*<<< orphan*/  mba; TYPE_1__ pmcw; } ;

/* Variables and functions */

__attribute__((used)) static void cio_apply_config(struct subchannel *sch, struct schib *schib)
{
	schib->pmcw.intparm = sch->config.intparm;
	schib->pmcw.mbi = sch->config.mbi;
	schib->pmcw.isc = sch->config.isc;
	schib->pmcw.ena = sch->config.ena;
	schib->pmcw.mme = sch->config.mme;
	schib->pmcw.mp = sch->config.mp;
	schib->pmcw.csense = sch->config.csense;
	schib->pmcw.mbfc = sch->config.mbfc;
	if (sch->config.mbfc)
		schib->mba = sch->config.mba;
}
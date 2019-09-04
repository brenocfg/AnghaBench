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
struct TYPE_4__ {scalar_t__ intparm; scalar_t__ mbi; scalar_t__ isc; scalar_t__ ena; scalar_t__ mme; scalar_t__ mp; scalar_t__ csense; scalar_t__ mbfc; scalar_t__ mba; } ;
struct subchannel {TYPE_2__ config; } ;
struct TYPE_3__ {scalar_t__ intparm; scalar_t__ mbi; scalar_t__ isc; scalar_t__ ena; scalar_t__ mme; scalar_t__ mp; scalar_t__ csense; scalar_t__ mbfc; } ;
struct schib {scalar_t__ mba; TYPE_1__ pmcw; } ;

/* Variables and functions */

__attribute__((used)) static int cio_check_config(struct subchannel *sch, struct schib *schib)
{
	return (schib->pmcw.intparm == sch->config.intparm) &&
		(schib->pmcw.mbi == sch->config.mbi) &&
		(schib->pmcw.isc == sch->config.isc) &&
		(schib->pmcw.ena == sch->config.ena) &&
		(schib->pmcw.mme == sch->config.mme) &&
		(schib->pmcw.mp == sch->config.mp) &&
		(schib->pmcw.csense == sch->config.csense) &&
		(schib->pmcw.mbfc == sch->config.mbfc) &&
		(!sch->config.mbfc || (schib->mba == sch->config.mba));
}
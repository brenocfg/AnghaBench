#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ word; } ;
struct TYPE_8__ {TYPE_2__ _xstart; int /*<<< orphan*/  xstarti; } ;
struct TYPE_6__ {int /*<<< orphan*/  config; } ;
struct TYPE_9__ {TYPE_3__ set; TYPE_1__ cset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FONT_DATA ; 
 int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  NPORT_CFG_GD0 ; 
 int /*<<< orphan*/  TESTVAL ; 
 scalar_t__ XSTI_TO_FXSTART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * font_data ; 
 int /*<<< orphan*/  newport_get_revisions () ; 
 int /*<<< orphan*/  newport_get_screensize () ; 
 int newport_has_init ; 
 int /*<<< orphan*/  newport_reset () ; 
 scalar_t__ newport_wait (TYPE_4__*) ; 
 TYPE_4__* npregs ; 

__attribute__((used)) static const char *newport_startup(void)
{
	int i;

	npregs->cset.config = NPORT_CFG_GD0;

	if (newport_wait(npregs))
		goto out_unmap;

	npregs->set.xstarti = TESTVAL;
	if (npregs->set._xstart.word != XSTI_TO_FXSTART(TESTVAL))
		goto out_unmap;

	for (i = 0; i < MAX_NR_CONSOLES; i++)
		font_data[i] = FONT_DATA;

	newport_reset();
	newport_get_revisions();
	newport_get_screensize();
	newport_has_init = 1;

	return "SGI Newport";

out_unmap:
	return NULL;
}
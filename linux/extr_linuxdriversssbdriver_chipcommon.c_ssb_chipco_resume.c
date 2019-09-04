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
struct ssb_chipcommon {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_CLKMODE_FAST ; 
 int /*<<< orphan*/  chipco_powercontrol_init (struct ssb_chipcommon*) ; 
 int /*<<< orphan*/  ssb_chipco_set_clockmode (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 

void ssb_chipco_resume(struct ssb_chipcommon *cc)
{
	if (!cc->dev)
		return;
	chipco_powercontrol_init(cc);
	ssb_chipco_set_clockmode(cc, SSB_CLKMODE_FAST);
}
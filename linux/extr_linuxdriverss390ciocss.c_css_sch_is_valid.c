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
struct TYPE_2__ {scalar_t__ st; int /*<<< orphan*/  w; int /*<<< orphan*/  dnv; } ;
struct schib {TYPE_1__ pmcw; } ;

/* Variables and functions */
 scalar_t__ SUBCHANNEL_TYPE_IO ; 
 scalar_t__ SUBCHANNEL_TYPE_MSG ; 

int css_sch_is_valid(struct schib *schib)
{
	if ((schib->pmcw.st == SUBCHANNEL_TYPE_IO) && !schib->pmcw.dnv)
		return 0;
	if ((schib->pmcw.st == SUBCHANNEL_TYPE_MSG) && !schib->pmcw.w)
		return 0;
	return 1;
}
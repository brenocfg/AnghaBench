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
struct fb_par_control {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * regs; int /*<<< orphan*/ * clock_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmode ; 
 TYPE_1__ regvals ; 
 int /*<<< orphan*/  vxres ; 
 int /*<<< orphan*/  vyres ; 
 int /*<<< orphan*/  xres ; 
 int /*<<< orphan*/  yres ; 

__attribute__((used)) static inline int PAR_EQUAL(struct fb_par_control *x, struct fb_par_control *y)
{
	int i, results;

	results = 1;
	for (i = 0; i < 3; i++)
		results &= !DIRTY(regvals.clock_params[i]);
	if (!results)
		return 0;
	for (i = 0; i < 16; i++)
		results &= !DIRTY(regvals.regs[i]);
	if (!results)
		return 0;
	return (!DIRTY(cmode) && !DIRTY(xres) && !DIRTY(yres)
		&& !DIRTY(vxres) && !DIRTY(vyres));
}
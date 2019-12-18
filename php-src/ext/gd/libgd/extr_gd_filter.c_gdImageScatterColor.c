#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sub; int plus; int* colors; unsigned int num_colors; int /*<<< orphan*/  seed; } ;
typedef  TYPE_1__ gdScatter ;
typedef  int /*<<< orphan*/  gdImagePtr ;

/* Variables and functions */
 int /*<<< orphan*/  GD_SCATTER_SEED () ; 
 int gdImageScatterEx (int /*<<< orphan*/ ,TYPE_1__*) ; 

int gdImageScatterColor(gdImagePtr im, int sub, int plus, int colors[], unsigned int num_colors)
{
	gdScatter s;

	s.sub = sub;
	s.plus = plus;
	s.colors = colors;
	s.num_colors = num_colors;
	s.seed = GD_SCATTER_SEED();
	return gdImageScatterEx(im, &s);
}
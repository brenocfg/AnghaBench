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
typedef  TYPE_1__* gdImagePtr ;
typedef  int /*<<< orphan*/  gdFixed ;
struct TYPE_3__ {int** tpixels; } ;

/* Variables and functions */
 int _color_blend (int const,int) ; 
 scalar_t__ gd_fxtof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gd_itofx (int) ; 
 int /*<<< orphan*/  gd_mulfx (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline int _setEdgePixel(const gdImagePtr src, unsigned int x, unsigned int y, gdFixed coverage, const int bgColor)
{
	const gdFixed f_127 = gd_itofx(127);
	register int c = src->tpixels[y][x];
	c = c | (( (int) (gd_fxtof(gd_mulfx(coverage, f_127)) + 50.5f)) << 24);
	return _color_blend(bgColor, c);
}
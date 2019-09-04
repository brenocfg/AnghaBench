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
typedef  int /*<<< orphan*/  gdImagePtr ;

/* Variables and functions */
 int gdImageConvolution (int /*<<< orphan*/ ,float**,int,int /*<<< orphan*/ ) ; 

int gdImageGaussianBlur(gdImagePtr im)
{
	float filter[3][3] =	{{1.0,2.0,1.0},
				{2.0,4.0,2.0},
				{1.0,2.0,1.0}};

	return gdImageConvolution(im, filter, 16, 0);
}
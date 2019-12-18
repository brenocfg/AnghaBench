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
 int gdImageConvolution (int /*<<< orphan*/ ,float**,float,int /*<<< orphan*/ ) ; 

int gdImageSmooth(gdImagePtr im, float weight)
{
	float filter[3][3] =	{{1.0,1.0,1.0},
				{1.0,0.0,1.0},
				{1.0,1.0,1.0}};

	filter[1][1] = weight;

	return gdImageConvolution(im, filter, weight+8, 0);
}
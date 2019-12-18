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
typedef  scalar_t__ int8_t ;

/* Variables and functions */

__attribute__((used)) static double ln(double x) {
	double y = (x-1)/(x+1);
	double y2 = y*y;
	double r = 0;
	for (int8_t i=33; i>0; i-=2) { //we've got the power
		r = 1.0/(double)i + y2 * r;
	}
	return 2*y*r;
}
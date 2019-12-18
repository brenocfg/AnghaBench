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
typedef  int uint64_t ;
typedef  double double_t ;

/* Variables and functions */
 double toint ; 

double rint(double x)
{
	union {double f; uint64_t i;} u = {x};
	int e = u.i>>52 & 0x7ff;
	int s = u.i>>63;
	double_t y;

	if (e >= 0x3ff+52)
		return x;
	if (s)
		y = x - toint + toint;
	else
		y = x + toint - toint;
	if (y == 0)
		return s ? -0.0 : 0;
	return y;
}
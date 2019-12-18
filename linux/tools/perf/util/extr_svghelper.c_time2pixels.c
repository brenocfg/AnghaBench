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
typedef  double u64 ;

/* Variables and functions */
 double first_time ; 
 double last_time ; 
 double svg_page_width ; 

__attribute__((used)) static double time2pixels(u64 __time)
{
	double X;

	X = 1.0 * svg_page_width * (__time - first_time) / (last_time - first_time);
	return X;
}
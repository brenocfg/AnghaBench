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
struct timeval {double tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 double USEC_PER_SEC ; 

__attribute__((used)) static double timeval2double(struct timeval *t)
{
	return t->tv_sec + (double) t->tv_usec/USEC_PER_SEC;
}
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
typedef  double double_t ;

/* Variables and functions */
 int N ; 
 double* Sden ; 
 double* Snum ; 

__attribute__((used)) static double S(double x)
{
	double_t num = 0, den = 0;
	int i;

	/* to avoid overflow handle large x differently */
	if (x < 8)
		for (i = N; i >= 0; i--) {
			num = num * x + Snum[i];
			den = den * x + Sden[i];
		}
	else
		for (i = 0; i <= N; i++) {
			num = num / x + Snum[i];
			den = den / x + Sden[i];
		}
	return num/den;
}
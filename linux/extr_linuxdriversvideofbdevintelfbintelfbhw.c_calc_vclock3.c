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
struct TYPE_2__ {int ref_clk; } ;

/* Variables and functions */
 TYPE_1__* plls ; 

__attribute__((used)) static int calc_vclock3(int index, int m, int n, int p)
{
	if (p == 0 || n == 0)
		return 0;
	return plls[index].ref_clk * m / n / p;
}
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

/* Variables and functions */
 int num_online_cpus () ; 

__attribute__((used)) static int compute_real(int n)
{
	int nr;

	if (n >= 0) {
		nr = n;
	} else {
		nr = num_online_cpus() + 1 + n;
		if (nr <= 0)
			nr = 1;
	}
	return nr;
}
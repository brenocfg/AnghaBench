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
 size_t RAND_MAX ; 
 size_t rand () ; 

size_t myrand(size_t max) {
	size_t loops = max / RAND_MAX;
	size_t i;

	size_t ret = rand();
	for(i = 0; i < loops ;i++)
		ret += rand();

	return ret % max;
}
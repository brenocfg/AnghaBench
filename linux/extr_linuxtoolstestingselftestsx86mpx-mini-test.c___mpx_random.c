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
 long random () ; 

long int __mpx_random(int line)
{
#ifdef NOT_SO_RANDOM
	static long fake = 722122311;
	fake += 563792075;
	return fakse;
#else
	return random();
#endif
}
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
 int /*<<< orphan*/  SIGALRM ; 
 int buffer ; 
 int count ; 
 scalar_t__ done ; 
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  interrupt ; 
 int ocount ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick () ; 

__attribute__((used)) static unsigned long
roulette()
{
#ifdef OLD_TRUERAND
	if (setjmp(env)) {
		count ^= (count>>3) ^ (count>>6) ^ ocount;
		count &= 0x7;
		ocount=count;
		buffer = (buffer<<3) ^ count;
		return buffer;
	}
#else
	done = 0;
#endif
	(void) signal(SIGALRM, interrupt);
	count = 0;
	tick();
#ifdef OLD_TRUERAND
	for (;;)
#else
	while(done == 0)
#endif
		count++;        /* about 1 MHz on VAX 11/780 */
#ifndef OLD_TRUERAND
	count ^= (count>>3) ^ (count>>6) ^ ocount;
	count &= 0x7;
	ocount=count;
	buffer = (buffer<<3) ^ count;
	return buffer;
#endif
}
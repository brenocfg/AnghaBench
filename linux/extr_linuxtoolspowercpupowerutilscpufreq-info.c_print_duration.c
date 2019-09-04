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
 scalar_t__ no_rounding ; 
 int /*<<< orphan*/  printf (char*,unsigned long,...) ; 

__attribute__((used)) static void print_duration(unsigned long duration)
{
	unsigned long tmp;

	if (no_rounding) {
		if (duration > 1000000)
			printf("%u.%06u ms", ((unsigned int) duration/1000000),
				((unsigned int) duration%1000000));
		else if (duration > 100000)
			printf("%u us", ((unsigned int) duration/1000));
		else if (duration > 1000)
			printf("%u.%03u us", ((unsigned int) duration/1000),
				((unsigned int) duration%1000));
		else
			printf("%lu ns", duration);
	} else {
		if (duration > 1000000) {
			tmp = duration%10000;
			if (tmp >= 5000)
				duration += 10000;
			printf("%u.%02u ms", ((unsigned int) duration/1000000),
				((unsigned int) (duration%1000000)/10000));
		} else if (duration > 100000) {
			tmp = duration%1000;
			if (tmp >= 500)
				duration += 1000;
			printf("%u us", ((unsigned int) duration / 1000));
		} else if (duration > 1000) {
			tmp = duration%100;
			if (tmp >= 50)
				duration += 100;
			printf("%u.%01u us", ((unsigned int) duration/1000),
				((unsigned int) (duration%1000)/100));
		} else
			printf("%lu ns", duration);
	}
	return;
}
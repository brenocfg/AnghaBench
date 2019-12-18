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
 int /*<<< orphan*/  printf (char*,unsigned int,...) ; 

__attribute__((used)) static void print_speed(unsigned long speed)
{
	unsigned long tmp;

	if (no_rounding) {
		if (speed > 1000000)
			printf("%u.%06u GHz", ((unsigned int) speed/1000000),
				((unsigned int) speed%1000000));
		else if (speed > 1000)
			printf("%u.%03u MHz", ((unsigned int) speed/1000),
				(unsigned int) (speed%1000));
		else
			printf("%lu kHz", speed);
	} else {
		if (speed > 1000000) {
			tmp = speed%10000;
			if (tmp >= 5000)
				speed += 10000;
			printf("%u.%02u GHz", ((unsigned int) speed/1000000),
				((unsigned int) (speed%1000000)/10000));
		} else if (speed > 100000) {
			tmp = speed%1000;
			if (tmp >= 500)
				speed += 1000;
			printf("%u MHz", ((unsigned int) speed/1000));
		} else if (speed > 1000) {
			tmp = speed%100;
			if (tmp >= 50)
				speed += 100;
			printf("%u.%01u MHz", ((unsigned int) speed/1000),
				((unsigned int) (speed%1000)/100));
		}
	}

	return;
}
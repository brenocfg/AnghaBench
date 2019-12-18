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
 int /*<<< orphan*/  snd_BUG () ; 

__attribute__((used)) static unsigned char divisor_to_rate_register(unsigned int divisor)
{
	switch (divisor) {
	case 353:	return 1;
	case 529:	return 2;
	case 617:	return 3;
	case 1058:	return 4;
	case 1764:	return 5;
	case 2117:	return 6;
	case 2558:	return 7;
	default:
		if (divisor < 21 || divisor > 192) {
			snd_BUG();
			return 192;
		}
		return divisor;
	}
}
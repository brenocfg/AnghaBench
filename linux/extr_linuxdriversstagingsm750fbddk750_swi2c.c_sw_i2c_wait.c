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

__attribute__((used)) static void sw_i2c_wait(void)
{
	/* find a bug:
	 * peekIO method works well before suspend/resume
	 * but after suspend, peekIO(0x3ce,0x61) & 0x10
	 * always be non-zero,which makes the while loop
	 * never finish.
	 * use non-ultimate for loop below is safe
	 */

    /* Change wait algorithm to use PCI bus clock,
     * it's more reliable than counter loop ..
     * write 0x61 to 0x3ce and read from 0x3cf
     */
	int i, tmp;

	for (i = 0; i < 600; i++) {
		tmp = i;
		tmp += i;
	}
}
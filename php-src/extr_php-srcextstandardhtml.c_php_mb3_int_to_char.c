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
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline size_t php_mb3_int_to_char(unsigned char *buf, unsigned k)
{
	assert(k <= 0xFFFFFFU);
	/* one to three bytes */
	if (k <= 0xFFU) { /* 1 */
		buf[0] = k;
		return 1U;
	} else if (k <= 0xFFFFU) { /* 2 */
		buf[0] = k >> 8;
		buf[1] = k & 0xFFU;
		return 2U;
	} else {
		buf[0] = k >> 16;
		buf[1] = (k >> 8) & 0xFFU;
		buf[2] = k & 0xFFU;
		return 3U;
	}
}
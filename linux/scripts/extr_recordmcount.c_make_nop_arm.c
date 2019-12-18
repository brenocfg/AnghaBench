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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  bl_mcount_arm ; 
 int /*<<< orphan*/  ideal_nop ; 
 int /*<<< orphan*/  ideal_nop2_thumb ; 
 int /*<<< orphan*/  ideal_nop4_arm ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_arm ; 
 int /*<<< orphan*/  push_bl_mcount_thumb ; 
 scalar_t__ ulseek (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ uwrite (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int make_nop_arm(void *map, size_t const offset)
{
	char *ptr;
	int cnt = 1;
	int nop_size;
	size_t off = offset;

	ptr = map + offset;
	if (memcmp(ptr, bl_mcount_arm, 4) == 0) {
		if (memcmp(ptr - 4, push_arm, 4) == 0) {
			off -= 4;
			cnt = 2;
		}
		ideal_nop = ideal_nop4_arm;
		nop_size = 4;
	} else if (memcmp(ptr - 2, push_bl_mcount_thumb, 6) == 0) {
		cnt = 3;
		nop_size = 2;
		off -= 2;
		ideal_nop = ideal_nop2_thumb;
	} else
		return -1;

	/* Convert to nop */
	if (ulseek(off, SEEK_SET) < 0)
		return -1;

	do {
		if (uwrite(ideal_nop, nop_size) < 0)
			return -1;
	} while (--cnt > 0);

	return 0;
}
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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  tmsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void
TIFFSwabArrayOfLong8(register uint64* lp, tmsize_t n)
{
	register unsigned char *cp;
	register unsigned char t;
	assert(sizeof(uint64)==8);
	/* XXX unroll loop some */
	while (n-- > 0) {
		cp = (unsigned char *)lp;
		t = cp[7]; cp[7] = cp[0]; cp[0] = t;
		t = cp[6]; cp[6] = cp[1]; cp[1] = t;
		t = cp[5]; cp[5] = cp[2]; cp[2] = t;
		t = cp[4]; cp[4] = cp[3]; cp[3] = t;
		lp++;
	}
}
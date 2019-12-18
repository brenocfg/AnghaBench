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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  tmsize_t ;

/* Variables and functions */

void
TIFFSwabArrayOfTriples(register uint8* tp, tmsize_t n)
{
	unsigned char* cp;
	unsigned char t;

	/* XXX unroll loop some */
	while (n-- > 0) {
		cp = (unsigned char*) tp;
		t = cp[2]; cp[2] = cp[0]; cp[0] = t;
		tp += 3;
	}
}
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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  tmsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void
TIFFSwabArrayOfShort(register uint16* wp, tmsize_t n)
{
	register unsigned char* cp;
	register unsigned char t;
	assert(sizeof(uint16)==2);
	/* XXX unroll loop some */
	while (n-- > 0) {
		cp = (unsigned char*) wp;
		t = cp[1]; cp[1] = cp[0]; cp[0] = t;
		wp++;
	}
}
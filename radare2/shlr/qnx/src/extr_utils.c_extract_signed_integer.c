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
typedef  int ut8 ;
typedef  int LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,int) ; 

LONGEST
extract_signed_integer (const ut8 *addr, int len, int be) {
	LONGEST retval;
	const ut8 *p;
	const ut8 *startaddr = addr;
	const ut8 *endaddr = startaddr + len;

	if (len > (int)sizeof(LONGEST))
		eprintf (
			"This operation is not available on integers of more than %d byte(s)\n",
			(int)sizeof(LONGEST));

	/* Start at the most significant end of the integer, and work towards
 the least significant.  */
	if (be) {
		p = startaddr;
		/* Do the sign extension once at the start.  */
		retval = ((LONGEST)*p ^ 0x80) - 0x80;
		for (++p; p < endaddr; ++p)
			retval = (retval << 8) | *p;
	} else {
		p = endaddr - 1;
		/* Do the sign extension once at the start.  */
		retval = ((LONGEST)*p ^ 0x80) - 0x80;
		for (--p; p >= startaddr; --p)
			retval = (retval << 8) | *p;
	}
	return retval;
}
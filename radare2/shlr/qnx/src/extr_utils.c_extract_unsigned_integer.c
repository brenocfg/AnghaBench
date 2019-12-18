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
typedef  int ULONGEST ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,int) ; 

ULONGEST
extract_unsigned_integer (const ut8 *addr, int len, int be) {
	ULONGEST retval;
	const ut8 *p;
	const ut8 *startaddr = addr;
	const ut8 *endaddr = startaddr + len;

	if (len > (int)sizeof(LONGEST))
		eprintf (
			"This operation is not available on integers of more than %d byte(s)\n",
			(int)sizeof(LONGEST));

	/* Start at the most significant end of the integer, and work towards
 the least significant.  */
	retval = 0;
	if (be) {
		for (p = startaddr; p < endaddr; ++p)
			retval = (retval << 8) | *p;
	} else {
		for (p = endaddr - 1; p >= startaddr; --p)
			retval = (retval << 8) | *p;
	}
	return retval;
}
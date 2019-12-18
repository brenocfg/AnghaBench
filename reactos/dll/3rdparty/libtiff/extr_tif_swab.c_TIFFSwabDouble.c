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

void
TIFFSwabDouble(double *dp)
{
	register unsigned char* cp = (unsigned char*) dp;
	unsigned char t;
	assert(sizeof(double)==8);
	t = cp[7]; cp[7] = cp[0]; cp[0] = t;
	t = cp[6]; cp[6] = cp[1]; cp[1] = t;
	t = cp[5]; cp[5] = cp[2]; cp[2] = t;
	t = cp[4]; cp[4] = cp[3]; cp[3] = t;
}
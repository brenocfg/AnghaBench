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
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int /*<<< orphan*/  PGTYPESdate_julmdy (int /*<<< orphan*/ ,int*) ; 

int
rjulmdy(date d, short mdy[3])
{
	int			mdy_int[3];

	PGTYPESdate_julmdy(d, mdy_int);
	mdy[0] = (short) mdy_int[0];
	mdy[1] = (short) mdy_int[1];
	mdy[2] = (short) mdy_int[2];
	return 0;
}
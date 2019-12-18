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
 int /*<<< orphan*/  PGTYPESdate_mdyjul (int*,int /*<<< orphan*/ *) ; 

int
rmdyjul(short mdy[3], date * d)
{
	int			mdy_int[3];

	mdy_int[0] = mdy[0];
	mdy_int[1] = mdy[1];
	mdy_int[2] = mdy[2];
	PGTYPESdate_mdyjul(mdy_int, d);
	return 0;
}
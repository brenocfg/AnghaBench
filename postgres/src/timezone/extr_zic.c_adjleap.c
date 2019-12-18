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
typedef  int zic_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int SECSPERDAY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * corr ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int leapcnt ; 
 int tadd (int,int) ; 
 int* trans ; 

__attribute__((used)) static void
adjleap(void)
{
	int			i;
	zic_t		last = 0;
	zic_t		prevtrans = 0;

	/*
	 * propagate leap seconds forward
	 */
	for (i = 0; i < leapcnt; ++i)
	{
		if (trans[i] - prevtrans < 28 * SECSPERDAY)
		{
			error(_("Leap seconds too close together"));
			exit(EXIT_FAILURE);
		}
		prevtrans = trans[i];
		trans[i] = tadd(trans[i], last);
		last = corr[i] += last;
	}
}
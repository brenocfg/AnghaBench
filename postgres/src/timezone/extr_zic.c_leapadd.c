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
typedef  scalar_t__ zic_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int TZ_MAX_LEAPS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int* corr ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int leapcnt ; 
 int* roll ; 
 scalar_t__* trans ; 

__attribute__((used)) static void
leapadd(zic_t t, bool positive, int rolling, int count)
{
	int			i,
				j;

	if (leapcnt + (positive ? count : 1) > TZ_MAX_LEAPS)
	{
		error(_("too many leap seconds"));
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < leapcnt; ++i)
		if (t <= trans[i])
			break;
	do
	{
		for (j = leapcnt; j > i; --j)
		{
			trans[j] = trans[j - 1];
			corr[j] = corr[j - 1];
			roll[j] = roll[j - 1];
		}
		trans[i] = t;
		corr[i] = positive ? 1 : -count;
		roll[i] = rolling;
		++leapcnt;
	} while (positive && --count != 0);
}
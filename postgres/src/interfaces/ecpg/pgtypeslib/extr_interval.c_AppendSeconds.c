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
typedef  scalar_t__ fsec_t ;

/* Variables and functions */
 scalar_t__ Abs (scalar_t__) ; 
 int /*<<< orphan*/  TrimTrailingZeros (char*) ; 
 int abs (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static void
AppendSeconds(char *cp, int sec, fsec_t fsec, int precision, bool fillzeros)
{
	if (fsec == 0)
	{
		if (fillzeros)
			sprintf(cp, "%02d", abs(sec));
		else
			sprintf(cp, "%d", abs(sec));
	}
	else
	{
		if (fillzeros)
			sprintf(cp, "%02d.%0*d", abs(sec), precision, (int) Abs(fsec));
		else
			sprintf(cp, "%d.%0*d", abs(sec), precision, (int) Abs(fsec));
		TrimTrailingZeros(cp);
	}
}
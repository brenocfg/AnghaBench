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
typedef  scalar_t__ int16 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetInt16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
searchChar(Datum *nodeLabels, int nNodes, int16 c, int *i)
{
	int			StopLow = 0,
				StopHigh = nNodes;

	while (StopLow < StopHigh)
	{
		int			StopMiddle = (StopLow + StopHigh) >> 1;
		int16		middle = DatumGetInt16(nodeLabels[StopMiddle]);

		if (c < middle)
			StopHigh = StopMiddle;
		else if (c > middle)
			StopLow = StopMiddle + 1;
		else
		{
			*i = StopMiddle;
			return true;
		}
	}

	*i = StopHigh;
	return false;
}
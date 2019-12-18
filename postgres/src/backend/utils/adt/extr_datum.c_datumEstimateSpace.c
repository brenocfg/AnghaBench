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
typedef  int Size ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ EOH_get_flat_size (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED (int /*<<< orphan*/ ) ; 
 scalar_t__ datumGetSize (int /*<<< orphan*/ ,int,int) ; 

Size
datumEstimateSpace(Datum value, bool isnull, bool typByVal, int typLen)
{
	Size		sz = sizeof(int);

	if (!isnull)
	{
		/* no need to use add_size, can't overflow */
		if (typByVal)
			sz += sizeof(Datum);
		else if (typLen == -1 &&
				 VARATT_IS_EXTERNAL_EXPANDED(DatumGetPointer(value)))
		{
			/* Expanded objects need to be flattened, see comment below */
			sz += EOH_get_flat_size(DatumGetEOHP(value));
		}
		else
			sz += datumGetSize(value, typByVal, typLen);
	}

	return sz;
}
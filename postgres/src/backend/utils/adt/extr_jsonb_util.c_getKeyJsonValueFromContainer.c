#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_8__ {int /*<<< orphan*/ * children; } ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  TYPE_1__ JsonbContainer ;
typedef  int /*<<< orphan*/  JEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonContainerIsObject (TYPE_1__*) ; 
 int JsonContainerSize (TYPE_1__*) ; 
 int /*<<< orphan*/  fillJsonbValue (TYPE_1__*,int,char*,int,int /*<<< orphan*/ *) ; 
 int getJsonbLength (TYPE_1__*,int) ; 
 int getJsonbOffset (TYPE_1__*,int) ; 
 int lengthCompareJsonbString (char const*,int,char const*,int) ; 
 int /*<<< orphan*/ * palloc (int) ; 

JsonbValue *
getKeyJsonValueFromContainer(JsonbContainer *container,
							 const char *keyVal, int keyLen, JsonbValue *res)
{
	JEntry	   *children = container->children;
	int			count = JsonContainerSize(container);
	char	   *baseAddr;
	uint32		stopLow,
				stopHigh;

	Assert(JsonContainerIsObject(container));

	/* Quick out without a palloc cycle if object is empty */
	if (count <= 0)
		return NULL;

	/*
	 * Binary search the container. Since we know this is an object, account
	 * for *Pairs* of Jentrys
	 */
	baseAddr = (char *) (children + count * 2);
	stopLow = 0;
	stopHigh = count;
	while (stopLow < stopHigh)
	{
		uint32		stopMiddle;
		int			difference;
		const char *candidateVal;
		int			candidateLen;

		stopMiddle = stopLow + (stopHigh - stopLow) / 2;

		candidateVal = baseAddr + getJsonbOffset(container, stopMiddle);
		candidateLen = getJsonbLength(container, stopMiddle);

		difference = lengthCompareJsonbString(candidateVal, candidateLen,
											  keyVal, keyLen);

		if (difference == 0)
		{
			/* Found our key, return corresponding value */
			int			index = stopMiddle + count;

			if (!res)
				res = palloc(sizeof(JsonbValue));

			fillJsonbValue(container, index, baseAddr,
						   getJsonbOffset(container, index),
						   res);

			return res;
		}
		else
		{
			if (difference < 0)
				stopLow = stopMiddle + 1;
			else
				stopHigh = stopMiddle;
		}
	}

	/* Not found */
	return NULL;
}
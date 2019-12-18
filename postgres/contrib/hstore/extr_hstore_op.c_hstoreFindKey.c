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
typedef  int /*<<< orphan*/  HStore ;
typedef  int /*<<< orphan*/  HEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * ARRPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HSTORE_KEY (int /*<<< orphan*/ *,char*,int) ; 
 int HSTORE_KEYLEN (int /*<<< orphan*/ *,int) ; 
 int HS_COUNT (int /*<<< orphan*/ *) ; 
 char* STRPTR (int /*<<< orphan*/ *) ; 
 int memcmp (int /*<<< orphan*/ ,char*,int) ; 

int
hstoreFindKey(HStore *hs, int *lowbound, char *key, int keylen)
{
	HEntry	   *entries = ARRPTR(hs);
	int			stopLow = lowbound ? *lowbound : 0;
	int			stopHigh = HS_COUNT(hs);
	int			stopMiddle;
	char	   *base = STRPTR(hs);

	while (stopLow < stopHigh)
	{
		int			difference;

		stopMiddle = stopLow + (stopHigh - stopLow) / 2;

		if (HSTORE_KEYLEN(entries, stopMiddle) == keylen)
			difference = memcmp(HSTORE_KEY(entries, base, stopMiddle), key, keylen);
		else
			difference = (HSTORE_KEYLEN(entries, stopMiddle) > keylen) ? 1 : -1;

		if (difference == 0)
		{
			if (lowbound)
				*lowbound = stopMiddle + 1;
			return stopMiddle;
		}
		else if (difference < 0)
			stopLow = stopMiddle + 1;
		else
			stopHigh = stopMiddle;
	}

	if (lowbound)
		*lowbound = stopLow;
	return -1;
}
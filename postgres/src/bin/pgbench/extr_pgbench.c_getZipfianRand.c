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
typedef  int int64 ;
typedef  int /*<<< orphan*/  RandomState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 double MAX_ZIPFIAN_PARAM ; 
 double MIN_ZIPFIAN_PARAM ; 
 int computeIterativeZipfian (int /*<<< orphan*/ *,int,double) ; 

__attribute__((used)) static int64
getZipfianRand(RandomState *random_state, int64 min, int64 max, double s)
{
	int64		n = max - min + 1;

	/* abort if parameter is invalid */
	Assert(MIN_ZIPFIAN_PARAM <= s && s <= MAX_ZIPFIAN_PARAM);

	return min - 1 + computeIterativeZipfian(random_state, n, s);
}
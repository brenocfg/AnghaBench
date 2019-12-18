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
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  MultiXactIdToOffsetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiXactOffsetCtl ; 
 int /*<<< orphan*/  PreviousMultiXactId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SimpleLruTruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
PerformOffsetsTruncation(MultiXactId oldestMulti, MultiXactId newOldestMulti)
{
	/*
	 * We step back one multixact to avoid passing a cutoff page that hasn't
	 * been created yet in the rare case that oldestMulti would be the first
	 * item on a page and oldestMulti == nextMulti.  In that case, if we
	 * didn't subtract one, we'd trigger SimpleLruTruncate's wraparound
	 * detection.
	 */
	SimpleLruTruncate(MultiXactOffsetCtl,
					  MultiXactIdToOffsetPage(PreviousMultiXactId(newOldestMulti)));
}
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
typedef  int /*<<< orphan*/  Pointer ;
typedef  int /*<<< orphan*/  PagetableEntry ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 long Max (long,int) ; 
 long Min (long,scalar_t__) ; 

long
tbm_calculate_entries(double maxbytes)
{
	long		nbuckets;

	/*
	 * Estimate number of hashtable entries we can have within maxbytes. This
	 * estimates the hash cost as sizeof(PagetableEntry), which is good enough
	 * for our purpose.  Also count an extra Pointer per entry for the arrays
	 * created during iteration readout.
	 */
	nbuckets = maxbytes /
		(sizeof(PagetableEntry) + sizeof(Pointer) + sizeof(Pointer));
	nbuckets = Min(nbuckets, INT_MAX - 1);	/* safety limit */
	nbuckets = Max(nbuckets, 16);	/* sanity limit */

	return nbuckets;
}
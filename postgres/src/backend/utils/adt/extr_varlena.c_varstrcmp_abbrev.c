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
typedef  int /*<<< orphan*/  SortSupport ;
typedef  scalar_t__ Datum ;

/* Variables and functions */

__attribute__((used)) static int
varstrcmp_abbrev(Datum x, Datum y, SortSupport ssup)
{
	/*
	 * When 0 is returned, the core system will call varstrfastcmp_c()
	 * (bpcharfastcmp_c() in BpChar case) or varlenafastcmp_locale().  Even a
	 * strcmp() on two non-truncated strxfrm() blobs cannot indicate *equality*
	 * authoritatively, for the same reason that there is a strcoll()
	 * tie-breaker call to strcmp() in varstr_cmp().
	 */
	if (x > y)
		return 1;
	else if (x == y)
		return 0;
	else
		return -1;
}
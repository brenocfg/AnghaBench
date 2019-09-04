#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  maxsector ;
typedef  scalar_t__ cdf_secid_t ;
struct TYPE_3__ {size_t sat_len; scalar_t__* sat_tab; } ;
typedef  TYPE_1__ cdf_sat_t ;

/* Variables and functions */
 size_t CDF_LOOP_LIMIT ; 
 scalar_t__ CDF_SECID_END_OF_CHAIN ; 
 scalar_t__ CDF_TOLE4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  EFTYPE ; 
 int /*<<< orphan*/  errno ; 

size_t
cdf_count_chain(const cdf_sat_t *sat, cdf_secid_t sid, size_t size)
{
	size_t i, j;
	cdf_secid_t maxsector = (cdf_secid_t)((sat->sat_len * size)
	    / sizeof(maxsector));

	DPRINTF(("Chain:"));
	if (sid == CDF_SECID_END_OF_CHAIN) {
		/* 0-length chain. */
		DPRINTF((" empty\n"));
		return 0;
	}

	for (j = i = 0; sid >= 0; i++, j++) {
		DPRINTF((" %d", sid));
		if (j >= CDF_LOOP_LIMIT) {
			DPRINTF(("Counting chain loop limit"));
			goto out;
		}
		if (sid >= maxsector) {
			DPRINTF(("Sector %d >= %d\n", sid, maxsector));
			goto out;
		}
		sid = CDF_TOLE4((uint32_t)sat->sat_tab[sid]);
	}
	if (i == 0) {
		DPRINTF((" none, sid: %d\n", sid));
		goto out;

	}
	DPRINTF(("\n"));
	return i;
out:
	errno = EFTYPE;
	return (size_t)-1;
}
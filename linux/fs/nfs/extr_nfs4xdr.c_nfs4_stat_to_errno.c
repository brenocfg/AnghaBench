#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int stat; int errno; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 TYPE_1__* nfs_errtbl ; 

__attribute__((used)) static int
nfs4_stat_to_errno(int stat)
{
	int i;
	for (i = 0; nfs_errtbl[i].stat != -1; i++) {
		if (nfs_errtbl[i].stat == stat)
			return nfs_errtbl[i].errno;
	}
	if (stat <= 10000 || stat > 10100) {
		/* The server is looney tunes. */
		return -EREMOTEIO;
	}
	/* If we cannot translate the error, the recovery routines should
	 * handle it.
	 * Note: remaining NFSv4 error codes have values > 10000, so should
	 * not conflict with native Linux error codes.
	 */
	return -stat;
}
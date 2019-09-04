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

/* Variables and functions */
 int NFSD_NRVERS ; 
 int /*<<< orphan*/  NFSD_SET ; 
 int /*<<< orphan*/  NFSD_TEST ; 
 scalar_t__ nfsd_minorversion (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd_vers (int,int /*<<< orphan*/ ) ; 

void nfsd_reset_versions(void)
{
	int i;

	for (i = 0; i < NFSD_NRVERS; i++)
		if (nfsd_vers(i, NFSD_TEST))
			return;

	for (i = 0; i < NFSD_NRVERS; i++)
		if (i != 4)
			nfsd_vers(i, NFSD_SET);
		else {
			int minor = 0;
			while (nfsd_minorversion(minor, NFSD_SET) >= 0)
				minor++;
		}
}
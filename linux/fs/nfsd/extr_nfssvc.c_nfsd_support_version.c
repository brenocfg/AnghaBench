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
 int NFSD_MINVERS ; 
 int NFSD_NRVERS ; 
 int /*<<< orphan*/ ** nfsd_version ; 

__attribute__((used)) static bool
nfsd_support_version(int vers)
{
	if (vers >= NFSD_MINVERS && vers < NFSD_NRVERS)
		return nfsd_version[vers] != NULL;
	return false;
}
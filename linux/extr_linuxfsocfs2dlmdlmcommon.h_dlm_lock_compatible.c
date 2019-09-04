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
 int LKM_EXMODE ; 
 int LKM_NLMODE ; 
 int LKM_PRMODE ; 

__attribute__((used)) static inline int dlm_lock_compatible(int existing, int request)
{
	/* NO_LOCK compatible with all */
	if (request == LKM_NLMODE ||
	    existing == LKM_NLMODE)
		return 1;

	/* EX incompatible with all non-NO_LOCK */
	if (request == LKM_EXMODE)
		return 0;

	/* request must be PR, which is compatible with PR */
	if (existing == LKM_PRMODE)
		return 1;

	return 0;
}
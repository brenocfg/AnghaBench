#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ MinBuildNumber; } ;
typedef  size_t SIZE_T ;
typedef  TYPE_1__* PKULL_M_PATCH_GENERIC ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */

PKULL_M_PATCH_GENERIC kull_m_patch_getGenericFromBuild(PKULL_M_PATCH_GENERIC generics, SIZE_T cbGenerics, DWORD BuildNumber)
{
	SIZE_T i;
	PKULL_M_PATCH_GENERIC current = NULL;

	for(i = 0; i < cbGenerics; i++)
	{
		if(generics[i].MinBuildNumber <= BuildNumber)
			current = &generics[i];
		else break;
	}
	return current;
}
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
struct TYPE_4__ {scalar_t__ OsIndex; } ;
typedef  size_t SIZE_T ;
typedef  TYPE_1__* PKKLL_M_MEMORY_GENERIC ;

/* Variables and functions */
 scalar_t__ KiwiOsIndex ; 

PKKLL_M_MEMORY_GENERIC kkll_m_memory_getGenericFromBuild(PKKLL_M_MEMORY_GENERIC generics, SIZE_T cbGenerics)
{
	SIZE_T i;
	for(i = 0; i < cbGenerics; i++)
		if(generics[i].OsIndex == KiwiOsIndex)
			return generics + i;
	return NULL;
}
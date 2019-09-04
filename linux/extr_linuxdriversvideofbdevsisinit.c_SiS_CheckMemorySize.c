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
struct SiS_Private {int VideoMemorySize; } ;

/* Variables and functions */
 unsigned short MemoryInfoFlag ; 
 unsigned short MemorySizeShift ; 
 unsigned short SiS_GetModeFlag (struct SiS_Private*,unsigned short,unsigned short) ; 

__attribute__((used)) static bool
SiS_CheckMemorySize(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex)
{
   unsigned short AdapterMemSize = SiS_Pr->VideoMemorySize / (1024*1024);
   unsigned short modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);
   unsigned short memorysize = ((modeflag & MemoryInfoFlag) >> MemorySizeShift) + 1;

   if(!AdapterMemSize) return true;

   if(AdapterMemSize < memorysize) return false;
   return true;
}
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
typedef  int ULONG ;
struct TYPE_4__ {int BasePage; int PageCount; int /*<<< orphan*/  MemoryType; } ;
typedef  TYPE_1__* PFREELDR_MEMORY_DESCRIPTOR ;

/* Variables and functions */
 int AvailableMemoryMb ; 
 int InstalledMemoryMb ; 
 int /*<<< orphan*/  LoaderFirmwarePermanent ; 
 int /*<<< orphan*/  LoaderFree ; 
 int MM_PAGE_SIZE ; 
 TYPE_1__* XboxMemoryMap ; 

PFREELDR_MEMORY_DESCRIPTOR
XboxMemGetMemoryMap(ULONG *MemoryMapSize)
{
  /* Synthesize memory map */
      /* Available RAM block */
      XboxMemoryMap[0].BasePage = 0;
      XboxMemoryMap[0].PageCount = AvailableMemoryMb * 1024 * 1024 / MM_PAGE_SIZE;
      XboxMemoryMap[0].MemoryType = LoaderFree;

      /* Video memory */
      XboxMemoryMap[1].BasePage = AvailableMemoryMb * 1024 * 1024 / MM_PAGE_SIZE;
      XboxMemoryMap[1].PageCount = (InstalledMemoryMb - AvailableMemoryMb) * 1024 * 1024 / MM_PAGE_SIZE;
      XboxMemoryMap[1].MemoryType = LoaderFirmwarePermanent;

  *MemoryMapSize = 2;
  return XboxMemoryMap;
}
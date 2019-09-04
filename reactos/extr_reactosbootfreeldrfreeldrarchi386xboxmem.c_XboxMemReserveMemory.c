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
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * PVOID ;

/* Variables and functions */
 int AvailableMemoryMb ; 
 scalar_t__ InstalledMemoryMb ; 
 int /*<<< orphan*/  XboxMemInit () ; 

PVOID
XboxMemReserveMemory(ULONG MbToReserve)
{
  if (0 == InstalledMemoryMb)
    {
      /* Hmm, seems we're not initialized yet */
      XboxMemInit();
    }

  if (AvailableMemoryMb < MbToReserve)
    {
      /* Can't satisfy the request */
      return NULL;
    }

  AvailableMemoryMb -= MbToReserve;

  /* Top of available memory points to the space just reserved */
  return (PVOID) (AvailableMemoryMb * 1024 * 1024);
}
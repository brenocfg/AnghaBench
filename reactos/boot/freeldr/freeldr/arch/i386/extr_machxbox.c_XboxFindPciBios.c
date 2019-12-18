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
struct TYPE_3__ {int NoBuses; int MajorRevision; int HardwareMechanism; scalar_t__ MinorRevision; } ;
typedef  TYPE_1__* PPCI_REGISTRY_INFO ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
XboxFindPciBios(PPCI_REGISTRY_INFO BusData)
{
    /* We emulate PCI BIOS here, there are 2 known working PCI buses on an original Xbox */

    BusData->NoBuses = 2;
    BusData->MajorRevision = 1;
    BusData->MinorRevision = 0;
    BusData->HardwareMechanism = 1;
    return TRUE;
}
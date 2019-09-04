#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_5__ {TYPE_1__ DriverVersion; int /*<<< orphan*/  Revision; int /*<<< orphan*/  SubSysId; int /*<<< orphan*/  DeviceId; int /*<<< orphan*/  VendorId; int /*<<< orphan*/  DeviceIdentifier; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ D3DADAPTER_IDENTIFIER9 ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_DirectDraw ; 

__attribute__((used)) static void GenerateDeviceIdentifier(D3DADAPTER_IDENTIFIER9* pIdentifier)
{
    DWORD* dwIdentifier = (DWORD*)&pIdentifier->DeviceIdentifier;

    pIdentifier->DeviceIdentifier = CLSID_DirectDraw;

    dwIdentifier[0] ^= pIdentifier->VendorId;
    dwIdentifier[1] ^= pIdentifier->DeviceId;
    dwIdentifier[2] ^= pIdentifier->SubSysId;
    dwIdentifier[3] ^= pIdentifier->Revision;
    dwIdentifier[2] ^= pIdentifier->DriverVersion.LowPart;
    dwIdentifier[3] ^= pIdentifier->DriverVersion.HighPart;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_5__ {int /*<<< orphan*/ * RootFcb; } ;
typedef  int /*<<< orphan*/ * PVFATFCB ;
typedef  TYPE_1__* PDEVICE_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 int /*<<< orphan*/ * vfatGrabFCBFromTable (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vfatMakeRootFCB (TYPE_1__*) ; 

PVFATFCB
vfatOpenRootFCB(
    PDEVICE_EXTENSION pVCB)
{
    PVFATFCB FCB;
    UNICODE_STRING NameU = RTL_CONSTANT_STRING(L"\\");

    FCB = vfatGrabFCBFromTable(pVCB, &NameU);
    if (FCB == NULL)
    {
        FCB = vfatMakeRootFCB(pVCB);
    }
    ASSERT(FCB == pVCB->RootFcb);

    return FCB;
}
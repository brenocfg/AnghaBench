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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {scalar_t__ bModified; } ;
typedef  TYPE_1__* PVIRTMEM ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDS_INFOREBOOT ; 
 int /*<<< orphan*/  IDS_MESSAGEBOXTITLE ; 
 int MB_ICONINFORMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  ResourceMessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WritePageFileSettings (TYPE_1__*) ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static VOID
OnVirtMemDialogOk(PVIRTMEM pVirtMem)
{
    if (pVirtMem->bModified != FALSE)
    {
        ResourceMessageBox(hApplet,
                           NULL,
                           MB_ICONINFORMATION | MB_OK,
                           IDS_MESSAGEBOXTITLE,
                           IDS_INFOREBOOT);

        WritePageFileSettings(pVirtMem);
    }
}
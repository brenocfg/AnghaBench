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
struct TYPE_4__ {void* Options; void* Description; void* BinPath; void* DisplayName; void* ServiceName; } ;
typedef  TYPE_1__* PCREATE_DATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* GetStringFromDialog (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_CREATE_DESC ; 
 int /*<<< orphan*/  IDC_CREATE_DISPNAME ; 
 int /*<<< orphan*/  IDC_CREATE_OPTIONS ; 
 int /*<<< orphan*/  IDC_CREATE_PATH ; 
 int /*<<< orphan*/  IDC_CREATE_SERVNAME ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
GetDataFromDialog(PCREATE_DATA Data)
{
    BOOL bRet = FALSE;

    if ((Data->ServiceName = GetStringFromDialog(Data, IDC_CREATE_SERVNAME)))
    {
        if ((Data->DisplayName = GetStringFromDialog(Data, IDC_CREATE_DISPNAME)))
        {
            if ((Data->BinPath = GetStringFromDialog(Data, IDC_CREATE_PATH)))
            {
                Data->Description = GetStringFromDialog(Data, IDC_CREATE_DESC);
                Data->Options = GetStringFromDialog(Data, IDC_CREATE_OPTIONS);

                bRet = TRUE;
            }
        }
    }

    return bRet;
}
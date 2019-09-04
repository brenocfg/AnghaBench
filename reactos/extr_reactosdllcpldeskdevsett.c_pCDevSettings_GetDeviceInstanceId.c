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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  const* PWSTR ;
typedef  int /*<<< orphan*/  const* LPWSTR ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  int /*<<< orphan*/  DEVINSTID_W ;
typedef  int /*<<< orphan*/  DEVINST ;
typedef  scalar_t__ CONFIGRET ;

/* Variables and functions */
 scalar_t__ CM_Get_Device_IDW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CM_Get_Device_ID_Size (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CM_LOCATE_DEVNODE_NORMAL ; 
 scalar_t__ CM_Locate_DevNodeW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CR_SUCCESS ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  LMEM_FIXED ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PWSTR
pCDevSettings_GetDeviceInstanceId(const WCHAR *pszDevice)
{
    DEVINST DevInst;
    CONFIGRET cr;
    ULONG BufLen;
    LPWSTR lpDevInstId = NULL;

    DPRINT1("CDevSettings::GetDeviceInstanceId(%ws) UNIMPLEMENTED!\n", pszDevice);

    cr = CM_Locate_DevNodeW(&DevInst,
                            (DEVINSTID_W)pszDevice,
                            CM_LOCATE_DEVNODE_NORMAL);
    if (cr == CR_SUCCESS)
    {
        DPRINT1("Success1\n");
        cr = CM_Get_Device_ID_Size(&BufLen,
                                   DevInst,
                                   0);
        if (cr == CR_SUCCESS)
        {
            DPRINT1("Success2\n");
            lpDevInstId = LocalAlloc(LMEM_FIXED,
                                     (BufLen + 1) * sizeof(WCHAR));

            if (lpDevInstId != NULL)
            {
                DPRINT1("Success3\n");
                cr = CM_Get_Device_IDW(DevInst,
                                       lpDevInstId,
                                       BufLen,
                                       0);

                if (cr != CR_SUCCESS)
                {
                    LocalFree((HLOCAL)lpDevInstId);
                    lpDevInstId = NULL;
                }
                DPRINT1("instance id: %ws\n", lpDevInstId);
            }
        }
    }

    return lpDevInstId;
}
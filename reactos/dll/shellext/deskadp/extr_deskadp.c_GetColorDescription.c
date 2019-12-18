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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int dmBitsPerPel; } ;
typedef  TYPE_1__* PDEVMODEW ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ IDS_15BPP ; 
 scalar_t__ IDS_16BPP ; 
 scalar_t__ IDS_24BPP ; 
 scalar_t__ IDS_32BPP ; 
 scalar_t__ IDS_4BPP ; 
 scalar_t__ IDS_8BPP ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char) ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static VOID
GetColorDescription(PDEVMODEW lpDevMode,
                    LPTSTR lpBuffer,
                    DWORD dwBufferLen)
{
    UINT uid = 0;

    switch (lpDevMode->dmBitsPerPel)
    {
        case 4:
            uid = IDS_4BPP;
            break;
        case 8:
            uid = IDS_8BPP;
            break;
        case 15:
            uid = IDS_15BPP;
            break;
        case 16:
            uid = IDS_16BPP;
            break;
        case 24:
            uid = IDS_24BPP;
            break;
        case 32:
            uid = IDS_32BPP;
            break;
    }

    if (uid == 0 ||
        !LoadString(hInstance,
                    uid,
                    lpBuffer,
                    dwBufferLen))
    {
        lpBuffer[0] = TEXT('\0');
    }
}
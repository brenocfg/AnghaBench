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
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/  (* LPDSENUMCALLBACKW ) (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  (* LPDSENUMCALLBACKA ) (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  DriverNameA ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (char*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LoadResourceString (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscpy (char*,char*) ; 

BOOL
DoDSoundCallback(
    LPDSENUMCALLBACKA lpDSEnumCallbackA,
    LPDSENUMCALLBACKW lpDSEnumCallbackW,
    LPGUID DeviceGuid,
    UINT ResourceId,
    LPWSTR ProductName,
    LPWSTR DriverName,
    LPVOID lpContext)
{
    WCHAR Buffer[200] = {0};
    char DriverNameA[200];

    static LPWSTR SoundDriverW = L"Primary Sound Driver";
    static LPWSTR SoundDriverA = L"Primary Sound Driver";

    if (lpDSEnumCallbackW)
    {
        if (ResourceId)
        {
            /* load resource string */
            Buffer[0] = 0;
            LoadResourceString(ResourceId, (LPVOID)Buffer, sizeof(Buffer)/sizeof(WCHAR), (LPVOID)SoundDriverW, TRUE);
            Buffer[(sizeof(Buffer)/sizeof(WCHAR))-1] = '\0';
        }
        else
        {
            /* use passed string */
            ASSERT(ProductName);
            wcscpy(Buffer, ProductName);
        }

        /* perform callback */
        return lpDSEnumCallbackW(DeviceGuid, Buffer, DriverName, lpContext);
    }
    else
    {
        if (ResourceId)
        {
            /* load resource string */
            Buffer[0] = 0;
            LoadResourceString(ResourceId, (LPVOID)Buffer, sizeof(Buffer)/sizeof(char), (LPVOID)SoundDriverA, FALSE);
            Buffer[(sizeof(Buffer)/sizeof(WCHAR))-1] = 0;
        }
        else
        {
            /* use passed string */
            Buffer[0] = 0;
            WideCharToMultiByte(CP_ACP, 0, ProductName, -1, (LPSTR)Buffer, sizeof(Buffer) / sizeof(char), NULL, NULL);
            Buffer[(sizeof(Buffer)/sizeof(WCHAR))-1] = 0;
        }

        DriverNameA[0] = 0;
        if (ProductName)
        {
            WideCharToMultiByte(CP_ACP, 0, ProductName, -1, DriverNameA, sizeof(DriverNameA) / sizeof(char), NULL, NULL);
            DriverNameA[(sizeof(DriverNameA) / sizeof(char))-1] = 0;
        }

        return lpDSEnumCallbackA(DeviceGuid, (LPSTR)Buffer, DriverNameA, lpContext);
    }
}
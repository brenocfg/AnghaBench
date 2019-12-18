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
struct TYPE_4__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetUserSidStringFromToken (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HKEY_USERS ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
HKEY
GetCurrentUserKey(HANDLE hToken)
{
    LONG Error;
    UNICODE_STRING SidString;
    HKEY hKey;

    if (!GetUserSidStringFromToken(hToken, &SidString))
    {
        DPRINT1("GetUserSidFromToken() failed\n");
        return NULL;
    }

    Error = RegOpenKeyExW(HKEY_USERS,
                          SidString.Buffer,
                          0,
                          MAXIMUM_ALLOWED,
                          &hKey);
    if (Error != ERROR_SUCCESS)
    {
        DPRINT1("RegOpenKeyExW() failed (Error %ld)\n", Error);
        RtlFreeUnicodeString(&SidString);
        SetLastError((DWORD)Error);
        return NULL;
    }

    RtlFreeUnicodeString(&SidString);

    return hKey;
}
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
typedef  int /*<<< orphan*/ * LPDWORD ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int strlen (int /*<<< orphan*/ ) ; 
 char* strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ParseField(LPCSTR lpszDeviceKey, LPDWORD pField, LPCSTR lpszSubString)
{
    const char* ResultStr;
    ResultStr = strstr(lpszDeviceKey, lpszSubString);
    if (ResultStr != NULL)
    {
        *pField = strtol(ResultStr + strlen(lpszSubString), NULL, 16);
    }
}
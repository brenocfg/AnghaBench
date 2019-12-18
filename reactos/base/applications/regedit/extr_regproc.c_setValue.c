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
typedef  int /*<<< orphan*/  dwData ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_DATA ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetWideStringN (char*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REGPROC_unescape_string (char*) ; 
 scalar_t__ REG_BINARY ; 
 scalar_t__ REG_DWORD ; 
 scalar_t__ REG_EXPAND_SZ ; 
 scalar_t__ REG_MULTI_SZ ; 
 scalar_t__ REG_SZ ; 
 scalar_t__ RegDeleteValueW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * convertHexCSVToHex (char*,scalar_t__*) ; 
 int /*<<< orphan*/  convertHexToDWord (char*,scalar_t__*) ; 
 int /*<<< orphan*/  currentKeyHandle ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getAppName () ; 
 scalar_t__ getDataType (char**,scalar_t__*) ; 
 scalar_t__ lstrcmpW (char*,char*) ; 
 scalar_t__ lstrlenW (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static LONG setValue(WCHAR* val_name, WCHAR* val_data, BOOL is_unicode)
{
    LONG res;
    DWORD  dwDataType, dwParseType;
    LPBYTE lpbData;
    DWORD  dwData, dwLen;
    WCHAR del[] = {'-',0};

    if ( (val_name == NULL) || (val_data == NULL) )
        return ERROR_INVALID_PARAMETER;

    if (lstrcmpW(val_data, del) == 0)
    {
        res=RegDeleteValueW(currentKeyHandle,val_name);
        return (res == ERROR_FILE_NOT_FOUND ? ERROR_SUCCESS : res);
    }

    /* Get the data type stored into the value field */
    dwDataType = getDataType(&val_data, &dwParseType);

    if (dwParseType == REG_SZ)          /* no conversion for string */
    {
        REGPROC_unescape_string(val_data);
        /* Compute dwLen after REGPROC_unescape_string because it may
         * have changed the string length and we don't want to store
         * the extra garbage in the registry.
         */
        dwLen = lstrlenW(val_data);
        if(val_data[dwLen-1] != '"')
            return ERROR_INVALID_DATA;
        if (dwLen>0 && val_data[dwLen-1]=='"')
        {
            dwLen--;
            val_data[dwLen]='\0';
        }
        lpbData = (BYTE*) val_data;
        dwLen++;  /* include terminating null */
        dwLen = dwLen * sizeof(WCHAR); /* size is in bytes */
    }
    else if (dwParseType == REG_DWORD)  /* Convert the dword types */
    {
        if (!convertHexToDWord(val_data, &dwData))
            return ERROR_INVALID_DATA;
        lpbData = (BYTE*)&dwData;
        dwLen = sizeof(dwData);
    }
    else if (dwParseType == REG_BINARY) /* Convert the binary data */
    {
        lpbData = convertHexCSVToHex(val_data, &dwLen);
        if (!lpbData)
            return ERROR_INVALID_DATA;

        if((dwDataType == REG_MULTI_SZ || dwDataType == REG_EXPAND_SZ) && !is_unicode)
        {
            LPBYTE tmp = lpbData;
            lpbData = (LPBYTE)GetWideStringN((char*)lpbData, dwLen, &dwLen);
            dwLen *= sizeof(WCHAR);
            HeapFree(GetProcessHeap(), 0, tmp);
        }
    }
    else                                /* unknown format */
    {
        fprintf(stderr,"%S: ERROR, unknown data format\n", getAppName());
        return ERROR_INVALID_DATA;
    }

    res = RegSetValueExW(
               currentKeyHandle,
               val_name,
               0,                  /* Reserved */
               dwDataType,
               lpbData,
               dwLen);
    if (dwParseType == REG_BINARY)
        HeapFree(GetProcessHeap(), 0, lpbData);
    return res;
}
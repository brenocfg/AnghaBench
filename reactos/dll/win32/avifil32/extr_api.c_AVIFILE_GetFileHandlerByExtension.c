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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPCLSID ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ AVIFILE_CLSIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 scalar_t__ RegQueryValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * wcsrchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  wsprintfA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL AVIFILE_GetFileHandlerByExtension(LPCWSTR szFile, LPCLSID lpclsid)
{
  CHAR   szRegKey[25];
  CHAR   szValue[100];
  LPWSTR szExt = wcsrchr(szFile, '.');
  LONG   len = ARRAY_SIZE(szValue);

  if (szExt == NULL)
    return FALSE;

  szExt++;

  wsprintfA(szRegKey, "AVIFile\\Extensions\\%.3ls", szExt);
  if (RegQueryValueA(HKEY_CLASSES_ROOT, szRegKey, szValue, &len) != ERROR_SUCCESS)
    return FALSE;

  return (AVIFILE_CLSIDFromString(szValue, lpclsid) == S_OK);
}
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
struct TYPE_4__ {scalar_t__ cFormatTags; int /*<<< orphan*/ * aFormatTag; int /*<<< orphan*/  fdwSupport; int /*<<< orphan*/  cFilterTags; } ;
typedef  TYPE_1__* PWINE_ACMDRIVERID ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MSACM_GetRegistryKey (TYPE_1__*) ; 
 int /*<<< orphan*/  MSACM_hHeap ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,void*,int*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL MSACM_ReadCache(PWINE_ACMDRIVERID padid)
{
    LPWSTR	key = MSACM_GetRegistryKey(padid);
    HKEY	hKey;
    DWORD	type, size;

    if (!key) return FALSE;

    padid->aFormatTag = NULL;

    if (RegCreateKeyW(HKEY_LOCAL_MACHINE, key, &hKey))
	goto errCleanUp;

    size = sizeof(padid->cFormatTags);
    if (RegQueryValueExA(hKey, "cFormatTags", 0, &type, (void*)&padid->cFormatTags, &size))
	goto errCleanUp;
    size = sizeof(padid->cFilterTags);
    if (RegQueryValueExA(hKey, "cFilterTags", 0, &type, (void*)&padid->cFilterTags, &size))
	goto errCleanUp;
    size = sizeof(padid->fdwSupport);
    if (RegQueryValueExA(hKey, "fdwSupport", 0, &type, (void*)&padid->fdwSupport, &size))
	goto errCleanUp;

    if (padid->cFormatTags > 0) {
	size = padid->cFormatTags * sizeof(padid->aFormatTag[0]);
	padid->aFormatTag = HeapAlloc(MSACM_hHeap, HEAP_ZERO_MEMORY, size);
	if (!padid->aFormatTag) goto errCleanUp;
	if (RegQueryValueExA(hKey, "aFormatTagCache", 0, &type, (void*)padid->aFormatTag, &size))
	    goto errCleanUp;
    }
    HeapFree(MSACM_hHeap, 0, key);
    return TRUE;

 errCleanUp:
    HeapFree(MSACM_hHeap, 0, key);
    HeapFree(MSACM_hHeap, 0, padid->aFormatTag);
    padid->aFormatTag = NULL;
    RegCloseKey(hKey);
    return FALSE;
}
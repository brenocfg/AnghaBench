#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WNetProviderTable ;
typedef  int /*<<< orphan*/  WNetProvider ;
typedef  char WCHAR ;
struct TYPE_2__ {scalar_t__ numAllocated; scalar_t__* entireNetwork; } ;
typedef  char* PWSTR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IDS_ENTIRENETWORK ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenCurrentUser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  _restoreSavedConnection (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _tryLoadProvider (char*) ; 
 char* debugstr_w (char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* providerTable ; 
 char* wcschr (char*,char) ; 

void wnetInit(HINSTANCE hInstDll)
{
    static const WCHAR providerOrderKey[] = { 'S','y','s','t','e','m','\\',
     'C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\',
     'C','o','n','t','r','o','l','\\',
     'N','e','t','w','o','r','k','P','r','o','v','i','d','e','r','\\',
     'O','r','d','e','r',0 };
     static const WCHAR providerOrder[] = { 'P','r','o','v','i','d','e','r',
      'O','r','d','e','r',0 };
    HKEY hKey;

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, providerOrderKey, 0, KEY_READ, &hKey)
     == ERROR_SUCCESS)
    {
        DWORD size = 0;

        RegQueryValueExW(hKey, providerOrder, NULL, NULL, NULL, &size);
        if (size)
        {
            PWSTR providers = HeapAlloc(GetProcessHeap(), 0, size);

            if (providers)
            {
                DWORD type;

                if (RegQueryValueExW(hKey, providerOrder, NULL, &type,
                 (LPBYTE)providers, &size) == ERROR_SUCCESS && type == REG_SZ)
                {
                    PWSTR ptr;
                    DWORD numToAllocate;

                    TRACE("provider order is %s\n", debugstr_w(providers));
                    /* first count commas as a heuristic for how many to
                     * allocate space for */
                    for (ptr = providers, numToAllocate = 1; ptr; )
                    {
                        ptr = wcschr(ptr, ',');
                        if (ptr) {
                            numToAllocate++;
                            ptr++;
                        }
                    }
                    providerTable =
                     HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                     sizeof(WNetProviderTable)
                     + (numToAllocate - 1) * sizeof(WNetProvider));
                    if (providerTable)
                    {
                        PWSTR ptrPrev;
                        int entireNetworkLen;
                        LPCWSTR stringresource;

                        entireNetworkLen = LoadStringW(hInstDll,
                         IDS_ENTIRENETWORK, (LPWSTR)&stringresource, 0);
                        providerTable->entireNetwork = HeapAlloc(
                         GetProcessHeap(), 0, (entireNetworkLen + 1) *
                         sizeof(WCHAR));
                        if (providerTable->entireNetwork)
                        {
                            memcpy(providerTable->entireNetwork, stringresource, entireNetworkLen*sizeof(WCHAR));
                            providerTable->entireNetwork[entireNetworkLen] = 0;
                        }
                        providerTable->numAllocated = numToAllocate;
                        for (ptr = providers; ptr; )
                        {
                            ptrPrev = ptr;
                            ptr = wcschr(ptr, ',');
                            if (ptr)
                                *ptr++ = '\0';
                            _tryLoadProvider(ptrPrev);
                        }
                    }
                }
                HeapFree(GetProcessHeap(), 0, providers);
            }
        }
        RegCloseKey(hKey);
    }

#ifdef __REACTOS__
    if (providerTable)
    {
        HKEY user_profile;

        if (RegOpenCurrentUser(KEY_ALL_ACCESS, &user_profile) == ERROR_SUCCESS)
        {
            HKEY network;
            WCHAR subkey[8] = {'N', 'e', 't', 'w', 'o', 'r', 'k', 0};

            if (RegOpenKeyExW(user_profile, subkey, 0, KEY_READ, &network) == ERROR_SUCCESS)
            {
                DWORD size, max;

                TRACE("Enumerating remembered connections\n");

                if (RegQueryInfoKey(network, NULL, NULL, NULL, &max, &size, NULL, NULL, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
                {
                    WCHAR *local;

                    TRACE("There are %lu connections\n", max);

                    local = HeapAlloc(GetProcessHeap(), 0, (size + 1) * sizeof(WCHAR));
                    if (local)
                    {
                        DWORD index;

                        for (index = 0; index < max; ++index)
                        {
                            DWORD len = size + 1;
                            HKEY connection;

                            TRACE("Trying connection %lu\n", index);

                            if (RegEnumKeyExW(network, index, local, &len, NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
                                continue;

                            TRACE("It is %S\n", local);

                            if (RegOpenKeyExW(network, local, 0, KEY_READ, &connection) != ERROR_SUCCESS)
                                continue;

                            _restoreSavedConnection(connection, local);
                            RegCloseKey(connection);
                        }

                        HeapFree(GetProcessHeap(), 0, local);
                    }
                }

                RegCloseKey(network);
            }

            RegCloseKey(user_profile);
        }
    }
#endif
}
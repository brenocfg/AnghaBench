#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  wMinorVerNum; int /*<<< orphan*/  wMajorVerNum; int /*<<< orphan*/  guid; } ;
struct TYPE_5__ {int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ TYPEATTR ;
typedef  TYPE_2__ TLIBATTR ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  char* LPOLESTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  const BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int KEY_WRITE ; 
 char* ProxyStubClsid32W ; 
 char* ProxyStubClsidW ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,char*,int) ; 
 char* TypeLibW ; 
 int /*<<< orphan*/  get_interface_key (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlenW (char*) ; 

__attribute__((used)) static void TLB_register_interface(TLIBATTR *libattr, LPOLESTR name, TYPEATTR *tattr, DWORD flag)
{
    WCHAR keyName[60];
    HKEY key, subKey;

    static const WCHAR PSOA[] = {'{','0','0','0','2','0','4','2','4','-',
                                 '0','0','0','0','-','0','0','0','0','-','C','0','0','0','-',
                                 '0','0','0','0','0','0','0','0','0','0','4','6','}',0};

    get_interface_key( &tattr->guid, keyName );
    if (RegCreateKeyExW(HKEY_CLASSES_ROOT, keyName, 0, NULL, 0,
                        KEY_WRITE | flag, NULL, &key, NULL) == ERROR_SUCCESS)
    {
        if (name)
            RegSetValueExW(key, NULL, 0, REG_SZ,
                           (BYTE *)name, (strlenW(name)+1) * sizeof(OLECHAR));

        if (RegCreateKeyExW(key, ProxyStubClsidW, 0, NULL, 0,
            KEY_WRITE | flag, NULL, &subKey, NULL) == ERROR_SUCCESS) {
            RegSetValueExW(subKey, NULL, 0, REG_SZ,
                           (const BYTE *)PSOA, sizeof PSOA);
            RegCloseKey(subKey);
        }

        if (RegCreateKeyExW(key, ProxyStubClsid32W, 0, NULL, 0,
            KEY_WRITE | flag, NULL, &subKey, NULL) == ERROR_SUCCESS) {
            RegSetValueExW(subKey, NULL, 0, REG_SZ,
                           (const BYTE *)PSOA, sizeof PSOA);
            RegCloseKey(subKey);
        }

        if (RegCreateKeyExW(key, TypeLibW, 0, NULL, 0,
            KEY_WRITE | flag, NULL, &subKey, NULL) == ERROR_SUCCESS)
        {
            WCHAR buffer[40];
            static const WCHAR fmtver[] = {'%','x','.','%','x',0 };
            static const WCHAR VersionW[] = {'V','e','r','s','i','o','n',0};

            StringFromGUID2(&libattr->guid, buffer, 40);
            RegSetValueExW(subKey, NULL, 0, REG_SZ,
                           (BYTE *)buffer, (strlenW(buffer)+1) * sizeof(WCHAR));
            sprintfW(buffer, fmtver, libattr->wMajorVerNum, libattr->wMinorVerNum);
            RegSetValueExW(subKey, VersionW, 0, REG_SZ,
                           (BYTE*)buffer, (strlenW(buffer)+1) * sizeof(WCHAR));
            RegCloseKey(subKey);
        }

        RegCloseKey(key);
    }
}
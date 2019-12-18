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
typedef  int /*<<< orphan*/  securityPkgNames ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ LSTATUS ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SECUR32_initKerberosSP () ; 
 int /*<<< orphan*/  SECUR32_initNTLMSP () ; 
 int /*<<< orphan*/  SECUR32_initNegotiateSP () ; 
 int /*<<< orphan*/  _tryLoadProvider (char*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ lstrlenW (char*) ; 
 int /*<<< orphan*/  securityProvidersKeyW ; 
 int /*<<< orphan*/  securityProvidersW ; 

__attribute__((used)) static void SECUR32_initializeProviders(void)
{
    HKEY key;
    LSTATUS apiRet;

    /* Now load providers from registry */
    apiRet = RegOpenKeyExW(HKEY_LOCAL_MACHINE, securityProvidersKeyW, 0,
     KEY_READ, &key);
    if (apiRet == ERROR_SUCCESS)
    {
        WCHAR securityPkgNames[MAX_PATH]; /* arbitrary len */
        DWORD size = sizeof(securityPkgNames), type;

        apiRet = RegQueryValueExW(key, securityProvidersW, NULL, &type,
         (PBYTE)securityPkgNames, &size);
        if (apiRet == ERROR_SUCCESS && type == REG_SZ)
        {
            WCHAR *ptr;

            size = size / sizeof(WCHAR);
            for (ptr = securityPkgNames;
              ptr < securityPkgNames + size; )
            {
                WCHAR *comma;

                for (comma = ptr; *comma && *comma != ','; comma++)
                    ;
                if (*comma == ',')
                    *comma = '\0';
                for (; *ptr && isspace(*ptr) && ptr < securityPkgNames + size;
                 ptr++)
                    ;
                if (*ptr)
                    _tryLoadProvider(ptr);
                ptr += lstrlenW(ptr) + 1;
            }
        }
        RegCloseKey(key);
    }

    /* Now load the built-in providers (in Wine, this is done before the registry loading) */
#ifdef __REACTOS__
/// FIXME: Interim Wine code until we get Samuel's rewrite!
    /* First load built-in providers */
    SECUR32_initNTLMSP();
    SECUR32_initKerberosSP();
    /* Load the Negotiate provider last so apps stumble over the working NTLM
     * provider first. Attempting to fix bug #16905 while keeping the
     * application reported on wine-users on 2006-09-12 working. */
    SECUR32_initNegotiateSP();
#endif

}
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
struct rc4_state {scalar_t__ hCryptProv; scalar_t__ hKey; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CryptDestroyKey (scalar_t__) ; 
 scalar_t__ CryptReleaseContext (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (void*) ; 

void
rdssl_rc4_info_delete(void* rc4_info)
{
    struct rc4_state *info = rc4_info;
    BOOL ret = TRUE;
    DWORD dwErr;
    if (!info)
    {
        //error("rdssl_rc4_info_delete rc4_info is null\n");
        return;
    }
    if (info->hKey)
    {
        ret = CryptDestroyKey(info->hKey);
        if (!ret)
        {
            dwErr = GetLastError();
            error("CryptDestroyKey failed with %lx\n", dwErr);
        }
    }
    if (info->hCryptProv)
    {
        ret = CryptReleaseContext(info->hCryptProv, 0);
        if (!ret)
        {
            dwErr = GetLastError();
            error("CryptReleaseContext failed with %lx\n", dwErr);
        }
    }
    g_free(rc4_info);
}
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
struct hash_context {int /*<<< orphan*/  hHash; int /*<<< orphan*/  hCryptProv; } ;
typedef  struct hash_context* DWORD ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 scalar_t__ CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptDestroyHash (int /*<<< orphan*/ ) ; 
 struct hash_context* GetLastError () ; 
 int /*<<< orphan*/  error (char*,struct hash_context*) ; 

void
rdssl_hash_clear(void* hash_info, ALG_ID id)
{
    struct hash_context *info = hash_info;
    BOOL ret;
    DWORD dwErr;
    if (!info || !info->hHash || !info->hCryptProv)
    {
        error("rdssl_hash_clear %p\n", info);
        return;
    }
    ret = CryptDestroyHash(info->hHash);
    if (!ret)
    {
        dwErr = GetLastError();
        error("CryptDestroyHash failed with %lx\n", dwErr);
        return;
    }
    ret = CryptCreateHash(info->hCryptProv,
                          id,
                          0,
                          0,
                          &info->hHash);
    if (!ret)
    {
        dwErr = GetLastError();
        error("CryptCreateHash failed with %lx\n", dwErr);
    }
}
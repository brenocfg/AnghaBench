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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CryptHashData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  error (char*,void*,...) ; 

void
rdssl_hash_transform(void* hash_info, char* data, int len)
{
    struct hash_context *info = hash_info;
    BOOL ret;
    DWORD dwErr;
    if (!info || !info->hHash || !info->hCryptProv || !data || !len)
    {
        error("rdssl_hash_transform %p %p %d\n", hash_info, data, len);
        return;
    }
    ret = CryptHashData(info->hHash,
                        (BYTE *)data,
                        len,
                        0);
    if (!ret)
    {
        dwErr = GetLastError();
        error("CryptHashData failed with %lx\n", dwErr);
    }
}
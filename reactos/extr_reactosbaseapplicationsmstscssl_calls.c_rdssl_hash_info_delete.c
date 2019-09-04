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
struct hash_context {scalar_t__ hCryptProv; scalar_t__ hHash; } ;

/* Variables and functions */
 int /*<<< orphan*/  CryptDestroyHash (scalar_t__) ; 
 int /*<<< orphan*/  CryptReleaseContext (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (void*) ; 

void
rdssl_hash_info_delete(void* hash_info)
{
    struct hash_context *info = hash_info;
    if (!info)
    {
        //error("ssl_hash_info_delete hash_info is null\n");
        return;
    }
    if (info->hHash)
    {
        CryptDestroyHash(info->hHash);
    }
    if (info->hCryptProv)
    {
        CryptReleaseContext(info->hCryptProv, 0);
    }
    g_free(hash_info);
}
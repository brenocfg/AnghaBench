#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
struct TYPE_3__ {void* (* enumContextsInStore ) (int /*<<< orphan*/ ,void const*) ;scalar_t__ (* serialize ) (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ;scalar_t__ (* getProp ) (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ;} ;
typedef  TYPE_1__ WINE_CONTEXT_INTERFACE ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_HASH_PROP_ID ; 
 scalar_t__ CRYPT_WriteSerializedToReg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Context_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  context_from_ptr (void const*) ; 
 void* stub1 (int /*<<< orphan*/ ,void const*) ; 
 scalar_t__ stub2 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ stub3 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ stub4 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

BOOL CRYPT_SerializeContextsToReg(HKEY key, DWORD flags,
 const WINE_CONTEXT_INTERFACE *contextInterface, HCERTSTORE memStore)
{
    const void *context = NULL;
    BOOL ret;

    do {
        context = contextInterface->enumContextsInStore(memStore, context);
        if (context)
        {
            BYTE hash[20];
            DWORD hashSize = sizeof(hash);

            ret = contextInterface->getProp(context, CERT_HASH_PROP_ID, hash,
             &hashSize);
            if (ret)
            {
                DWORD size = 0;
                LPBYTE buf = NULL;

                ret = contextInterface->serialize(context, 0, NULL, &size);
                if (size)
                    buf = CryptMemAlloc(size);
                if (buf)
                {
                    ret = contextInterface->serialize(context, 0, buf, &size);
                    if (ret)
                        ret = CRYPT_WriteSerializedToReg(key, flags, hash, buf, size);
                }
                CryptMemFree(buf);
            }
        }
        else
            ret = TRUE;
    } while (ret && context != NULL);
    if (context)
        Context_Release(context_from_ptr(context));
    return ret;
}
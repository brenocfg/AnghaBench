#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  properties; } ;
struct TYPE_6__ {scalar_t__ cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ CRYPT_DATA_BLOB ;
typedef  TYPE_2__ CDecodeMsg ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CDecodeHashMsg_GetParam (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  CMSG_COMPUTED_HASH_PARAM ; 
 int /*<<< orphan*/  CMSG_HASH_DATA_PARAM ; 
 int /*<<< orphan*/  CRYPT_E_HASH_VALUE ; 
 scalar_t__ ContextPropertyList_FindProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * CryptMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static BOOL CDecodeHashMsg_VerifyHash(CDecodeMsg *msg)
{
    BOOL ret;
    CRYPT_DATA_BLOB hashBlob;

    ret = ContextPropertyList_FindProperty(msg->properties,
     CMSG_HASH_DATA_PARAM, &hashBlob);
    if (ret)
    {
        DWORD computedHashSize = 0;

        ret = CDecodeHashMsg_GetParam(msg, CMSG_COMPUTED_HASH_PARAM, 0, NULL,
         &computedHashSize);
        if (hashBlob.cbData == computedHashSize)
        {
            LPBYTE computedHash = CryptMemAlloc(computedHashSize);

            if (computedHash)
            {
                ret = CDecodeHashMsg_GetParam(msg, CMSG_COMPUTED_HASH_PARAM, 0,
                 computedHash, &computedHashSize);
                if (ret)
                {
                    if (memcmp(hashBlob.pbData, computedHash, hashBlob.cbData))
                    {
                        SetLastError(CRYPT_E_HASH_VALUE);
                        ret = FALSE;
                    }
                }
                CryptMemFree(computedHash);
            }
            else
            {
                SetLastError(ERROR_OUTOFMEMORY);
                ret = FALSE;
            }
        }
        else
        {
            SetLastError(CRYPT_E_HASH_VALUE);
            ret = FALSE;
        }
    }
    return ret;
}
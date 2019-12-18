#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/ * pbData; } ;
struct TYPE_13__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/ * pbData; } ;
struct TYPE_12__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/ * pbData; } ;
struct TYPE_11__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/ * pbData; } ;
struct TYPE_10__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/ * pbData; } ;
struct TYPE_9__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/ * pbData; } ;
struct protect_data_t {TYPE_6__ fingerprint; TYPE_5__ cipher; TYPE_4__ salt; int /*<<< orphan*/  hash_len; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/  null1; TYPE_3__ data0; int /*<<< orphan*/  cipher_key_len; int /*<<< orphan*/  cipher_alg; int /*<<< orphan*/  szDataDescr; int /*<<< orphan*/  null0; TYPE_2__ info1; int /*<<< orphan*/  count1; TYPE_1__ info0; int /*<<< orphan*/  count0; } ;
struct TYPE_15__ {scalar_t__ cbData; int /*<<< orphan*/ * pbData; } ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_7__ DATA_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  unserialize_dword (int /*<<< orphan*/ *,scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unserialize_string (int /*<<< orphan*/ *,scalar_t__*,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
BOOL unserialize(const DATA_BLOB *pSerial, struct protect_data_t *pInfo)
{
    BYTE * ptr;
    DWORD index;
    DWORD size;
    BOOL status=TRUE;

    TRACE("called\n");

    if (!pInfo || !pSerial || !pSerial->pbData)
        return FALSE;

    index=0;
    ptr=pSerial->pbData;
    size=pSerial->cbData;

    /* count0 */
    if (!unserialize_dword(ptr,&index,size,&pInfo->count0))
    {
        ERR("reading count0 failed!\n");
        return FALSE;
    }
    
    /* info0 */
    if (!unserialize_string(ptr,&index,size,16,sizeof(BYTE),FALSE,
                            &pInfo->info0.pbData, &pInfo->info0.cbData))
    {
        ERR("reading info0 failed!\n");
        return FALSE;
    }

    /* count1 */
    if (!unserialize_dword(ptr,&index,size,&pInfo->count1))
    {
        ERR("reading count1 failed!\n");
        return FALSE;
    }

    /* info1 */
    if (!unserialize_string(ptr,&index,size,16,sizeof(BYTE),FALSE,
                            &pInfo->info1.pbData, &pInfo->info1.cbData))
    {
        ERR("reading info1 failed!\n");
        return FALSE;
    }

    /* null0 */
    if (!unserialize_dword(ptr,&index,size,&pInfo->null0))
    {
        ERR("reading null0 failed!\n");
        return FALSE;
    }
    
    /* szDataDescr */
    if (!unserialize_string(ptr,&index,size,0,sizeof(BYTE),TRUE,
                            (BYTE**)&pInfo->szDataDescr, NULL))
    {
        ERR("reading szDataDescr failed!\n");
        return FALSE;
    }

    /* cipher_alg */
    if (!unserialize_dword(ptr,&index,size,&pInfo->cipher_alg))
    {
        ERR("reading cipher_alg failed!\n");
        return FALSE;
    }
    
    /* cipher_key_len */
    if (!unserialize_dword(ptr,&index,size,&pInfo->cipher_key_len))
    {
        ERR("reading cipher_key_len failed!\n");
        return FALSE;
    }
    
    /* data0 */
    if (!unserialize_string(ptr,&index,size,0,sizeof(BYTE),TRUE,
                            &pInfo->data0.pbData, &pInfo->data0.cbData))
    {
        ERR("reading data0 failed!\n");
        return FALSE;
    }

    /* null1 */
    if (!unserialize_dword(ptr,&index,size,&pInfo->null1))
    {
        ERR("reading null1 failed!\n");
        return FALSE;
    }
    
    /* hash_alg */
    if (!unserialize_dword(ptr,&index,size,&pInfo->hash_alg))
    {
        ERR("reading hash_alg failed!\n");
        return FALSE;
    }
    
    /* hash_len */
    if (!unserialize_dword(ptr,&index,size,&pInfo->hash_len))
    {
        ERR("reading hash_len failed!\n");
        return FALSE;
    }
    
    /* salt */
    if (!unserialize_string(ptr,&index,size,0,sizeof(BYTE),TRUE,
                            &pInfo->salt.pbData, &pInfo->salt.cbData))
    {
        ERR("reading salt failed!\n");
        return FALSE;
    }

    /* cipher */
    if (!unserialize_string(ptr,&index,size,0,sizeof(BYTE),TRUE,
                            &pInfo->cipher.pbData, &pInfo->cipher.cbData))
    {
        ERR("reading cipher failed!\n");
        return FALSE;
    }

    /* fingerprint */
    if (!unserialize_string(ptr,&index,size,0,sizeof(BYTE),TRUE,
                            &pInfo->fingerprint.pbData, &pInfo->fingerprint.cbData))
    {
        ERR("reading fingerprint failed!\n");
        return FALSE;
    }

    /* allow structure size to be too big (since some applications
     * will pad this up to 256 bytes, it seems) */
    if (index>size)
    {
        /* this is an impossible-to-reach test, but if the padding
         * issue is ever understood, this may become more useful */
        ERR("loaded corrupt structure! (used %u expected %u)\n", index, size);
        status=FALSE;
    }

    return status;
}
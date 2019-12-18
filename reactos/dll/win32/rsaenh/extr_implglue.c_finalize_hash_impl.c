#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  digest; } ;
struct TYPE_6__ {int /*<<< orphan*/  digest; } ;
struct TYPE_5__ {int /*<<< orphan*/  sha512; int /*<<< orphan*/  sha384; int /*<<< orphan*/  sha256; int /*<<< orphan*/  sha; TYPE_3__ md5; TYPE_4__ md4; int /*<<< orphan*/  md2; } ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  TYPE_1__ HASH_CONTEXT ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int ALG_ID ;

/* Variables and functions */
 int /*<<< orphan*/  A_SHAFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  CALG_MD2 134 
#define  CALG_MD4 133 
#define  CALG_MD5 132 
#define  CALG_SHA 131 
#define  CALG_SHA_256 130 
#define  CALG_SHA_384 129 
#define  CALG_SHA_512 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MD4Final (TYPE_4__*) ; 
 int /*<<< orphan*/  MD5Final (TYPE_3__*) ; 
 int /*<<< orphan*/  NTE_BAD_ALGID ; 
 int /*<<< orphan*/  SHA256_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA384_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  md2_done (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

BOOL finalize_hash_impl(ALG_ID aiAlgid, HASH_CONTEXT *pHashContext, BYTE *pbHashValue) 
{
    switch (aiAlgid)
    {
        case CALG_MD2:
            md2_done(&pHashContext->md2, pbHashValue);
            break;
        
        case CALG_MD4:
            MD4Final(&pHashContext->md4);
            memcpy(pbHashValue, pHashContext->md4.digest, 16);
            break;
        
        case CALG_MD5:
            MD5Final(&pHashContext->md5);
            memcpy(pbHashValue, pHashContext->md5.digest, 16);
            break;
        
        case CALG_SHA:
            A_SHAFinal(&pHashContext->sha, (PULONG)pbHashValue);
            break;
        
        case CALG_SHA_256:
            SHA256_Final(pbHashValue, &pHashContext->sha256);
            break;

        case CALG_SHA_384:
            SHA384_Final(pbHashValue, &pHashContext->sha384);
            break;

        case CALG_SHA_512:
            SHA512_Final(pbHashValue, &pHashContext->sha512);
            break;

        default:
            SetLastError(NTE_BAD_ALGID);
            return FALSE;
    }

    return TRUE;
}
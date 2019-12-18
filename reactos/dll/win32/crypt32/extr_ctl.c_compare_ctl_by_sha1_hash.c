#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
struct TYPE_2__ {scalar_t__ cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/  PCCTL_CONTEXT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ CRYPT_HASH_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_SHA1_HASH_PROP_ID ; 
 int CertGetCTLContextProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int FALSE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static BOOL compare_ctl_by_sha1_hash(PCCTL_CONTEXT pCtlContext, DWORD dwType,
 DWORD dwFlags, const void *pvPara)
{
    BOOL ret;
    BYTE hash[20];
    DWORD size = sizeof(hash);

    ret = CertGetCTLContextProperty(pCtlContext, CERT_SHA1_HASH_PROP_ID, hash,
     &size);
    if (ret)
    {
        const CRYPT_HASH_BLOB *pHash = pvPara;

        if (size == pHash->cbData)
            ret = !memcmp(pHash->pbData, hash, size);
        else
            ret = FALSE;
    }
    return ret;
}
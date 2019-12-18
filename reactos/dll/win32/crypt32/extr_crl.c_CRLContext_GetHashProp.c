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
typedef  int /*<<< orphan*/  crl_t ;
struct TYPE_3__ {void* member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ CRYPT_DATA_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 scalar_t__ CRLContext_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ CryptHashCertificate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL CRLContext_GetHashProp(crl_t *crl, DWORD dwPropId,
 ALG_ID algID, const BYTE *toHash, DWORD toHashLen, void *pvData,
 DWORD *pcbData)
{
    BOOL ret = CryptHashCertificate(0, algID, 0, toHash, toHashLen, pvData,
     pcbData);
    if (ret && pvData)
    {
        CRYPT_DATA_BLOB blob = { *pcbData, pvData };

        ret = CRLContext_SetProperty(crl, dwPropId, 0, &blob);
    }
    return ret;
}
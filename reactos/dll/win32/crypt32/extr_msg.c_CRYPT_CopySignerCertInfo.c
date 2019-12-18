#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ cbData; } ;
struct TYPE_13__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
struct TYPE_9__ {TYPE_8__ SerialNumber; TYPE_8__ Issuer; } ;
struct TYPE_10__ {int /*<<< orphan*/  KeyId; TYPE_1__ IssuerSerialNumber; } ;
struct TYPE_11__ {scalar_t__ dwIdChoice; TYPE_2__ u; } ;
struct TYPE_12__ {TYPE_3__ SignerId; } ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_4__ CMSG_CMS_SIGNER_INFO ;
typedef  TYPE_5__ CERT_INFO ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CERT_ID_ISSUER_SERIAL_NUMBER ; 
 int /*<<< orphan*/  CRYPT_CopyBlob (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CRYPT_CopyKeyIdAsIssuerAndSerial (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ CRYPT_SizeOfKeyIdAsIssuerAndSerial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL CRYPT_CopySignerCertInfo(void *pvData, DWORD *pcbData,
 const CMSG_CMS_SIGNER_INFO *in)
{
    DWORD size = sizeof(CERT_INFO), rdnSize = 0;
    BOOL ret;

    TRACE("(%p, %d, %p)\n", pvData, pvData ? *pcbData : 0, in);

    if (in->SignerId.dwIdChoice == CERT_ID_ISSUER_SERIAL_NUMBER)
    {
        size += in->SignerId.u.IssuerSerialNumber.Issuer.cbData;
        size += in->SignerId.u.IssuerSerialNumber.SerialNumber.cbData;
    }
    else
    {
        rdnSize = CRYPT_SizeOfKeyIdAsIssuerAndSerial(&in->SignerId.u.KeyId);
        size += rdnSize;
    }
    if (!pvData)
    {
        *pcbData = size;
        ret = TRUE;
    }
    else if (*pcbData < size)
    {
        *pcbData = size;
        SetLastError(ERROR_MORE_DATA);
        ret = FALSE;
    }
    else
    {
        LPBYTE nextData = (BYTE *)pvData + sizeof(CERT_INFO);
        CERT_INFO *out = pvData;

        memset(out, 0, sizeof(CERT_INFO));
        if (in->SignerId.dwIdChoice == CERT_ID_ISSUER_SERIAL_NUMBER)
        {
            CRYPT_CopyBlob(&out->Issuer,
             &in->SignerId.u.IssuerSerialNumber.Issuer, &nextData);
            CRYPT_CopyBlob(&out->SerialNumber,
             &in->SignerId.u.IssuerSerialNumber.SerialNumber, &nextData);
            ret = TRUE;
        }
        else
            ret = CRYPT_CopyKeyIdAsIssuerAndSerial(&out->Issuer, &out->SerialNumber,
             &in->SignerId.u.KeyId, rdnSize, &nextData);
    }
    TRACE("returning %d\n", ret);
    return ret;
}
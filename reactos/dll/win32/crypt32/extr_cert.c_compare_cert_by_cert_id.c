#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pbData; int /*<<< orphan*/  cbData; } ;
struct TYPE_11__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
struct TYPE_13__ {TYPE_3__ KeyId; int /*<<< orphan*/  HashId; TYPE_2__ IssuerSerialNumber; } ;
struct TYPE_15__ {int dwIdChoice; TYPE_4__ u; } ;
struct TYPE_14__ {TYPE_1__* pCertInfo; int /*<<< orphan*/  dwCertEncodingType; } ;
struct TYPE_10__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
typedef  TYPE_5__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_6__ CERT_ID ;
typedef  int BOOL ;

/* Variables and functions */
#define  CERT_ID_ISSUER_SERIAL_NUMBER 130 
#define  CERT_ID_KEY_IDENTIFIER 129 
#define  CERT_ID_SHA1_HASH 128 
 int /*<<< orphan*/  CERT_KEY_IDENTIFIER_PROP_ID ; 
 int CertCompareCertificateName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CertCompareIntegerBlob (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CertGetCertificateContextProperty (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptMemAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int compare_cert_by_sha1_hash (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL compare_cert_by_cert_id(PCCERT_CONTEXT pCertContext, DWORD dwType,
 DWORD dwFlags, const void *pvPara)
{
    CERT_ID *id = (CERT_ID *)pvPara;
    BOOL ret;

    switch (id->dwIdChoice)
    {
    case CERT_ID_ISSUER_SERIAL_NUMBER:
        ret = CertCompareCertificateName(pCertContext->dwCertEncodingType,
         &pCertContext->pCertInfo->Issuer, &id->u.IssuerSerialNumber.Issuer);
        if (ret)
            ret = CertCompareIntegerBlob(&pCertContext->pCertInfo->SerialNumber,
             &id->u.IssuerSerialNumber.SerialNumber);
        break;
    case CERT_ID_SHA1_HASH:
        ret = compare_cert_by_sha1_hash(pCertContext, dwType, dwFlags,
         &id->u.HashId);
        break;
    case CERT_ID_KEY_IDENTIFIER:
    {
        DWORD size = 0;

        ret = CertGetCertificateContextProperty(pCertContext,
         CERT_KEY_IDENTIFIER_PROP_ID, NULL, &size);
        if (ret && size == id->u.KeyId.cbData)
        {
            LPBYTE buf = CryptMemAlloc(size);

            if (buf)
            {
                CertGetCertificateContextProperty(pCertContext,
                 CERT_KEY_IDENTIFIER_PROP_ID, buf, &size);
                ret = !memcmp(buf, id->u.KeyId.pbData, size);
                CryptMemFree(buf);
            }
            else
                ret = FALSE;
        }
        else
            ret = FALSE;
        break;
    }
    default:
        ret = FALSE;
        break;
    }
    return ret;
}
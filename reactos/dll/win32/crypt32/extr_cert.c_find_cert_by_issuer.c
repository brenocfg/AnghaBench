#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {TYPE_6__* pCertInfo; int /*<<< orphan*/  dwCertEncodingType; } ;
struct TYPE_24__ {scalar_t__ cbData; } ;
struct TYPE_27__ {TYPE_13__ DirectoryName; } ;
struct TYPE_32__ {scalar_t__ dwAltNameChoice; TYPE_3__ u; } ;
struct TYPE_25__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_31__ {TYPE_1__ Value; } ;
struct TYPE_28__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
struct TYPE_29__ {int /*<<< orphan*/  KeyId; TYPE_4__ IssuerSerialNumber; } ;
struct TYPE_22__ {TYPE_5__ u; void* dwIdChoice; } ;
struct TYPE_30__ {TYPE_10__ Issuer; int /*<<< orphan*/  rgExtension; int /*<<< orphan*/  cExtension; } ;
struct TYPE_26__ {size_t cAltEntry; TYPE_8__* rgAltEntry; } ;
struct TYPE_23__ {TYPE_13__ KeyId; TYPE_13__ AuthorityCertSerialNumber; TYPE_2__ AuthorityCertIssuer; TYPE_13__ CertSerialNumber; TYPE_13__ CertIssuer; } ;
typedef  TYPE_7__* PCERT_EXTENSION ;
typedef  TYPE_8__* PCERT_ALT_NAME_ENTRY ;
typedef  TYPE_9__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  CRYPT_INTEGER_BLOB ;
typedef  int /*<<< orphan*/  CRYPT_HASH_BLOB ;
typedef  int /*<<< orphan*/  CERT_NAME_BLOB ;
typedef  TYPE_10__ CERT_ID ;
typedef  TYPE_11__ CERT_AUTHORITY_KEY_ID_INFO ;
typedef  TYPE_11__ CERT_AUTHORITY_KEY_ID2_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CERT_ALT_NAME_DIRECTORY_NAME ; 
 size_t CERT_COMPARE_NAME ; 
 size_t CERT_COMPARE_SUBJECT_CERT ; 
 void* CERT_ID_ISSUER_SERIAL_NUMBER ; 
 void* CERT_ID_KEY_IDENTIFIER ; 
 int CRYPT_DECODE_ALLOC_FLAG ; 
 int CRYPT_DECODE_NOCOPY_FLAG ; 
 TYPE_7__* CertFindExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_11__**,size_t*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  LocalFree (TYPE_11__*) ; 
 int /*<<< orphan*/  X509_AUTHORITY_KEY_ID ; 
 int /*<<< orphan*/  X509_AUTHORITY_KEY_ID2 ; 
 TYPE_9__* cert_compare_certs_in_store (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,size_t,size_t,TYPE_10__*) ; 
 int /*<<< orphan*/  compare_cert_by_cert_id ; 
 int /*<<< orphan*/  compare_cert_by_name ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_13__*,int) ; 
 int /*<<< orphan*/  szOID_AUTHORITY_KEY_IDENTIFIER ; 
 int /*<<< orphan*/  szOID_AUTHORITY_KEY_IDENTIFIER2 ; 

__attribute__((used)) static PCCERT_CONTEXT find_cert_by_issuer(HCERTSTORE store, DWORD dwType,
 DWORD dwFlags, const void *pvPara, PCCERT_CONTEXT prev)
{
    BOOL ret;
    PCCERT_CONTEXT found = NULL, subject = pvPara;
    PCERT_EXTENSION ext;
    DWORD size;

    if ((ext = CertFindExtension(szOID_AUTHORITY_KEY_IDENTIFIER,
     subject->pCertInfo->cExtension, subject->pCertInfo->rgExtension)))
    {
        CERT_AUTHORITY_KEY_ID_INFO *info;

        ret = CryptDecodeObjectEx(subject->dwCertEncodingType,
         X509_AUTHORITY_KEY_ID, ext->Value.pbData, ext->Value.cbData,
         CRYPT_DECODE_ALLOC_FLAG | CRYPT_DECODE_NOCOPY_FLAG, NULL,
         &info, &size);
        if (ret)
        {
            CERT_ID id;

            if (info->CertIssuer.cbData && info->CertSerialNumber.cbData)
            {
                id.dwIdChoice = CERT_ID_ISSUER_SERIAL_NUMBER;
                memcpy(&id.u.IssuerSerialNumber.Issuer, &info->CertIssuer,
                 sizeof(CERT_NAME_BLOB));
                memcpy(&id.u.IssuerSerialNumber.SerialNumber,
                 &info->CertSerialNumber, sizeof(CRYPT_INTEGER_BLOB));
            }
            else if (info->KeyId.cbData)
            {
                id.dwIdChoice = CERT_ID_KEY_IDENTIFIER;
                memcpy(&id.u.KeyId, &info->KeyId, sizeof(CRYPT_HASH_BLOB));
            }
            else
                ret = FALSE;
            if (ret)
                found = cert_compare_certs_in_store(store, prev,
                 compare_cert_by_cert_id, dwType, dwFlags, &id);
            LocalFree(info);
        }
    }
    else if ((ext = CertFindExtension(szOID_AUTHORITY_KEY_IDENTIFIER2,
     subject->pCertInfo->cExtension, subject->pCertInfo->rgExtension)))
    {
        CERT_AUTHORITY_KEY_ID2_INFO *info;

        ret = CryptDecodeObjectEx(subject->dwCertEncodingType,
         X509_AUTHORITY_KEY_ID2, ext->Value.pbData, ext->Value.cbData,
         CRYPT_DECODE_ALLOC_FLAG | CRYPT_DECODE_NOCOPY_FLAG, NULL,
         &info, &size);
        if (ret)
        {
            CERT_ID id;

            if (info->AuthorityCertIssuer.cAltEntry &&
             info->AuthorityCertSerialNumber.cbData)
            {
                PCERT_ALT_NAME_ENTRY directoryName = NULL;
                DWORD i;

                for (i = 0; !directoryName &&
                 i < info->AuthorityCertIssuer.cAltEntry; i++)
                    if (info->AuthorityCertIssuer.rgAltEntry[i].dwAltNameChoice
                     == CERT_ALT_NAME_DIRECTORY_NAME)
                        directoryName =
                         &info->AuthorityCertIssuer.rgAltEntry[i];
                if (directoryName)
                {
                    id.dwIdChoice = CERT_ID_ISSUER_SERIAL_NUMBER;
                    memcpy(&id.u.IssuerSerialNumber.Issuer,
                     &directoryName->u.DirectoryName, sizeof(CERT_NAME_BLOB));
                    memcpy(&id.u.IssuerSerialNumber.SerialNumber,
                     &info->AuthorityCertSerialNumber,
                     sizeof(CRYPT_INTEGER_BLOB));
                }
                else
                {
                    FIXME("no supported name type in authority key id2\n");
                    ret = FALSE;
                }
            }
            else if (info->KeyId.cbData)
            {
                id.dwIdChoice = CERT_ID_KEY_IDENTIFIER;
                memcpy(&id.u.KeyId, &info->KeyId, sizeof(CRYPT_HASH_BLOB));
            }
            else
                ret = FALSE;
            if (ret)
                found = cert_compare_certs_in_store(store, prev,
                 compare_cert_by_cert_id, dwType, dwFlags, &id);
            LocalFree(info);
        }
    }
    else
       found = cert_compare_certs_in_store(store, prev,
        compare_cert_by_name, CERT_COMPARE_NAME | CERT_COMPARE_SUBJECT_CERT,
        dwFlags, &subject->pCertInfo->Issuer);
    return found;
}
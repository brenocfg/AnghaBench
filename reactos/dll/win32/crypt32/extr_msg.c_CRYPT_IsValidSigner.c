#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  cbData; } ;
struct TYPE_21__ {int /*<<< orphan*/  cbData; } ;
struct TYPE_20__ {int /*<<< orphan*/  cbData; } ;
struct TYPE_22__ {TYPE_5__ Issuer; TYPE_4__ SerialNumber; } ;
struct TYPE_24__ {TYPE_7__ KeyId; TYPE_6__ IssuerSerialNumber; } ;
struct TYPE_25__ {int dwIdChoice; TYPE_8__ u; } ;
struct TYPE_18__ {int /*<<< orphan*/  cbData; } ;
struct TYPE_17__ {int /*<<< orphan*/  cbData; } ;
struct TYPE_19__ {TYPE_2__ Issuer; TYPE_1__ SerialNumber; } ;
struct TYPE_15__ {int /*<<< orphan*/  pszObjId; } ;
struct TYPE_14__ {scalar_t__ pszObjId; } ;
struct TYPE_16__ {int cbSize; TYPE_11__ HashAlgorithm; int /*<<< orphan*/  hCryptProv; TYPE_10__ HashEncryptionAlgorithm; TYPE_9__ SignerId; TYPE_3__* pCertInfo; } ;
typedef  TYPE_12__ CMSG_SIGNER_ENCODE_INFO_WITH_CMS ;
typedef  int /*<<< orphan*/  CMSG_SIGNER_ENCODE_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CERT_ID_ISSUER_SERIAL_NUMBER 129 
#define  CERT_ID_KEY_IDENTIFIER 128 
 int /*<<< orphan*/  CRYPT_E_UNKNOWN_ALGO ; 
 int /*<<< orphan*/  CertOIDToAlgId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CRYPT_IsValidSigner(const CMSG_SIGNER_ENCODE_INFO_WITH_CMS *signer)
{
    if (signer->cbSize != sizeof(CMSG_SIGNER_ENCODE_INFO) &&
     signer->cbSize != sizeof(CMSG_SIGNER_ENCODE_INFO_WITH_CMS))
    {
        SetLastError(E_INVALIDARG);
        return FALSE;
    }
    if (signer->cbSize == sizeof(CMSG_SIGNER_ENCODE_INFO))
    {
        if (!signer->pCertInfo->SerialNumber.cbData)
        {
            SetLastError(E_INVALIDARG);
            return FALSE;
        }
        if (!signer->pCertInfo->Issuer.cbData)
        {
            SetLastError(E_INVALIDARG);
            return FALSE;
        }
    }
    else if (signer->cbSize == sizeof(CMSG_SIGNER_ENCODE_INFO_WITH_CMS))
    {
        switch (signer->SignerId.dwIdChoice)
        {
        case 0:
            if (!signer->pCertInfo->SerialNumber.cbData)
            {
                SetLastError(E_INVALIDARG);
                return FALSE;
            }
            if (!signer->pCertInfo->Issuer.cbData)
            {
                SetLastError(E_INVALIDARG);
                return FALSE;
            }
            break;
        case CERT_ID_ISSUER_SERIAL_NUMBER:
            if (!signer->SignerId.u.IssuerSerialNumber.SerialNumber.cbData)
            {
                SetLastError(E_INVALIDARG);
                return FALSE;
            }
            if (!signer->SignerId.u.IssuerSerialNumber.Issuer.cbData)
            {
                SetLastError(E_INVALIDARG);
                return FALSE;
            }
            break;
        case CERT_ID_KEY_IDENTIFIER:
            if (!signer->SignerId.u.KeyId.cbData)
            {
                SetLastError(E_INVALIDARG);
                return FALSE;
            }
            break;
        default:
            SetLastError(E_INVALIDARG);
        }
        if (signer->HashEncryptionAlgorithm.pszObjId)
        {
            FIXME("CMSG_SIGNER_ENCODE_INFO with CMS fields unsupported\n");
            return FALSE;
        }
    }
    if (!signer->hCryptProv)
    {
        SetLastError(E_INVALIDARG);
        return FALSE;
    }
    if (!CertOIDToAlgId(signer->HashAlgorithm.pszObjId))
    {
        SetLastError(CRYPT_E_UNKNOWN_ALGO);
        return FALSE;
    }
    return TRUE;
}
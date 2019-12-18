#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* info; int /*<<< orphan*/  signerHandles; } ;
struct TYPE_15__ {TYPE_2__ signed_data; } ;
struct TYPE_21__ {TYPE_3__ u; } ;
struct TYPE_20__ {int /*<<< orphan*/  SubjectPublicKeyInfo; int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
struct TYPE_16__ {int /*<<< orphan*/  SerialNumber; int /*<<< orphan*/  Issuer; } ;
struct TYPE_17__ {TYPE_4__ IssuerSerialNumber; } ;
struct TYPE_18__ {scalar_t__ dwIdChoice; TYPE_5__ u; } ;
struct TYPE_19__ {TYPE_6__ SignerId; } ;
struct TYPE_13__ {size_t cSignerInfo; TYPE_7__* rgSignerInfo; } ;
typedef  TYPE_7__* PCMSG_CMS_SIGNER_INFO ;
typedef  TYPE_8__* PCERT_INFO ;
typedef  size_t DWORD ;
typedef  TYPE_9__ CDecodeMsg ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CDecodeSignedMsg_VerifySignatureWithKey (TYPE_9__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ CERT_ID_ISSUER_SERIAL_NUMBER ; 
 int /*<<< orphan*/  CRYPT_E_SIGNER_NOT_FOUND ; 
 scalar_t__ CertCompareCertificateName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CertCompareIntegerBlob (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,size_t) ; 
 int /*<<< orphan*/  NTE_BAD_SIGNATURE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 

__attribute__((used)) static BOOL CDecodeSignedMsg_VerifySignature(CDecodeMsg *msg, PCERT_INFO info)
{
    BOOL ret = FALSE;
    DWORD i;

    if (!msg->u.signed_data.signerHandles)
    {
        SetLastError(NTE_BAD_SIGNATURE);
        return FALSE;
    }
    for (i = 0; !ret && i < msg->u.signed_data.info->cSignerInfo; i++)
    {
        PCMSG_CMS_SIGNER_INFO signerInfo =
         &msg->u.signed_data.info->rgSignerInfo[i];

        if (signerInfo->SignerId.dwIdChoice == CERT_ID_ISSUER_SERIAL_NUMBER)
        {
            ret = CertCompareCertificateName(X509_ASN_ENCODING,
             &signerInfo->SignerId.u.IssuerSerialNumber.Issuer,
             &info->Issuer);
            if (ret)
            {
                ret = CertCompareIntegerBlob(
                 &signerInfo->SignerId.u.IssuerSerialNumber.SerialNumber,
                 &info->SerialNumber);
                if (ret)
                    break;
            }
        }
        else
        {
            FIXME("signer %d: unimplemented for key id\n", i);
        }
    }
    if (ret)
        ret = CDecodeSignedMsg_VerifySignatureWithKey(msg, 0, i,
         &info->SubjectPublicKeyInfo);
    else
        SetLastError(CRYPT_E_SIGNER_NOT_FOUND);

    return ret;
}
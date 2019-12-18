#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int* pbData; int cbData; } ;
struct TYPE_21__ {int cSignerHandle; TYPE_6__* info; TYPE_3__* signerHandles; } ;
struct TYPE_22__ {TYPE_7__ signed_data; } ;
struct TYPE_18__ {int* pbData; int cbData; } ;
struct TYPE_19__ {int* pszObjId; TYPE_4__ Content; } ;
struct TYPE_20__ {int cSignerInfo; int cCertEncoded; int cCrlEncoded; int /*<<< orphan*/ * rgSignerInfo; TYPE_2__* rgCrlEncoded; TYPE_1__* rgCertEncoded; TYPE_5__ content; } ;
struct TYPE_17__ {int /*<<< orphan*/  contentHash; } ;
struct TYPE_16__ {int* pbData; int cbData; } ;
struct TYPE_15__ {int* pbData; int cbData; } ;
struct TYPE_14__ {int type; TYPE_8__ u; } ;
typedef  int DWORD ;
typedef  TYPE_9__ CRYPT_DATA_BLOB ;
typedef  TYPE_10__ CDecodeMsg ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CMSG_ATTR_CERT_COUNT_PARAM 142 
#define  CMSG_ATTR_CERT_PARAM 141 
#define  CMSG_CERT_COUNT_PARAM 140 
#define  CMSG_CERT_PARAM 139 
#define  CMSG_CMS_SIGNER_INFO_PARAM 138 
#define  CMSG_COMPUTED_HASH_PARAM 137 
#define  CMSG_CONTENT_PARAM 136 
#define  CMSG_CRL_COUNT_PARAM 135 
#define  CMSG_CRL_PARAM 134 
#define  CMSG_ENCODED_SIGNER 133 
#define  CMSG_INNER_CONTENT_TYPE_PARAM 132 
#define  CMSG_SIGNER_CERT_INFO_PARAM 131 
#define  CMSG_SIGNER_COUNT_PARAM 130 
#define  CMSG_SIGNER_INFO_PARAM 129 
#define  CMSG_TYPE_PARAM 128 
 int /*<<< orphan*/  CMS_SIGNER_INFO ; 
 int /*<<< orphan*/  CRYPT_CopyCMSSignerInfo (void*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPT_CopyParam (void*,int*,int*,int) ; 
 int /*<<< orphan*/  CRYPT_CopySignerCertInfo (void*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPT_CopySignerInfo (void*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 int /*<<< orphan*/  CRYPT_E_INVALID_INDEX ; 
 int /*<<< orphan*/  CRYPT_E_INVALID_MSG_TYPE ; 
 int /*<<< orphan*/  CryptDecodeObjectEx (int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_9__**,int*) ; 
 int /*<<< orphan*/  CryptEncodeObjectEx (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int*) ; 
 int /*<<< orphan*/  CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 int /*<<< orphan*/  LocalFree (TYPE_9__*) ; 
 int PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_OCTET_STRING ; 
 int /*<<< orphan*/  strcmp (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int*) ; 
 int /*<<< orphan*/  szOID_RSA_data ; 

__attribute__((used)) static BOOL CDecodeSignedMsg_GetParam(CDecodeMsg *msg, DWORD dwParamType,
 DWORD dwIndex, void *pvData, DWORD *pcbData)
{
    BOOL ret = FALSE;

    switch (dwParamType)
    {
    case CMSG_TYPE_PARAM:
        ret = CRYPT_CopyParam(pvData, pcbData, &msg->type, sizeof(msg->type));
        break;
    case CMSG_CONTENT_PARAM:
        if (msg->u.signed_data.info)
        {
            if (!strcmp(msg->u.signed_data.info->content.pszObjId,
             szOID_RSA_data))
            {
                CRYPT_DATA_BLOB *blob;
                DWORD size;

                ret = CryptDecodeObjectEx(X509_ASN_ENCODING, X509_OCTET_STRING,
                 msg->u.signed_data.info->content.Content.pbData,
                 msg->u.signed_data.info->content.Content.cbData,
                 CRYPT_DECODE_ALLOC_FLAG, NULL, &blob, &size);
                if (ret)
                {
                    ret = CRYPT_CopyParam(pvData, pcbData, blob->pbData,
                     blob->cbData);
                    LocalFree(blob);
                }
            }
            else
                ret = CRYPT_CopyParam(pvData, pcbData,
                 msg->u.signed_data.info->content.Content.pbData,
                 msg->u.signed_data.info->content.Content.cbData);
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_INNER_CONTENT_TYPE_PARAM:
        if (msg->u.signed_data.info)
            ret = CRYPT_CopyParam(pvData, pcbData,
             msg->u.signed_data.info->content.pszObjId,
             strlen(msg->u.signed_data.info->content.pszObjId) + 1);
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_SIGNER_COUNT_PARAM:
        if (msg->u.signed_data.info)
            ret = CRYPT_CopyParam(pvData, pcbData,
             &msg->u.signed_data.info->cSignerInfo, sizeof(DWORD));
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_SIGNER_INFO_PARAM:
        if (msg->u.signed_data.info)
        {
            if (dwIndex >= msg->u.signed_data.info->cSignerInfo)
                SetLastError(CRYPT_E_INVALID_INDEX);
            else
                ret = CRYPT_CopySignerInfo(pvData, pcbData,
                 &msg->u.signed_data.info->rgSignerInfo[dwIndex]);
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_SIGNER_CERT_INFO_PARAM:
        if (msg->u.signed_data.info)
        {
            if (dwIndex >= msg->u.signed_data.info->cSignerInfo)
                SetLastError(CRYPT_E_INVALID_INDEX);
            else
                ret = CRYPT_CopySignerCertInfo(pvData, pcbData,
                 &msg->u.signed_data.info->rgSignerInfo[dwIndex]);
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_CERT_COUNT_PARAM:
        if (msg->u.signed_data.info)
            ret = CRYPT_CopyParam(pvData, pcbData,
             &msg->u.signed_data.info->cCertEncoded, sizeof(DWORD));
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_CERT_PARAM:
        if (msg->u.signed_data.info)
        {
            if (dwIndex >= msg->u.signed_data.info->cCertEncoded)
                SetLastError(CRYPT_E_INVALID_INDEX);
            else
                ret = CRYPT_CopyParam(pvData, pcbData,
                 msg->u.signed_data.info->rgCertEncoded[dwIndex].pbData,
                 msg->u.signed_data.info->rgCertEncoded[dwIndex].cbData);
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_CRL_COUNT_PARAM:
        if (msg->u.signed_data.info)
            ret = CRYPT_CopyParam(pvData, pcbData,
             &msg->u.signed_data.info->cCrlEncoded, sizeof(DWORD));
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_CRL_PARAM:
        if (msg->u.signed_data.info)
        {
            if (dwIndex >= msg->u.signed_data.info->cCrlEncoded)
                SetLastError(CRYPT_E_INVALID_INDEX);
            else
                ret = CRYPT_CopyParam(pvData, pcbData,
                 msg->u.signed_data.info->rgCrlEncoded[dwIndex].pbData,
                 msg->u.signed_data.info->rgCrlEncoded[dwIndex].cbData);
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_COMPUTED_HASH_PARAM:
        if (msg->u.signed_data.info)
        {
            if (dwIndex >= msg->u.signed_data.cSignerHandle)
                SetLastError(CRYPT_E_INVALID_INDEX);
            else
                ret = CryptGetHashParam(
                 msg->u.signed_data.signerHandles[dwIndex].contentHash,
                 HP_HASHVAL, pvData, pcbData, 0);
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_ENCODED_SIGNER:
        if (msg->u.signed_data.info)
        {
            if (dwIndex >= msg->u.signed_data.info->cSignerInfo)
                SetLastError(CRYPT_E_INVALID_INDEX);
            else
                ret = CryptEncodeObjectEx(
                 X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, CMS_SIGNER_INFO,
                 &msg->u.signed_data.info->rgSignerInfo[dwIndex], 0, NULL,
                 pvData, pcbData);
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_ATTR_CERT_COUNT_PARAM:
        if (msg->u.signed_data.info)
        {
            DWORD attrCertCount = 0;

            ret = CRYPT_CopyParam(pvData, pcbData,
             &attrCertCount, sizeof(DWORD));
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_ATTR_CERT_PARAM:
        if (msg->u.signed_data.info)
            SetLastError(CRYPT_E_INVALID_INDEX);
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    case CMSG_CMS_SIGNER_INFO_PARAM:
        if (msg->u.signed_data.info)
        {
            if (dwIndex >= msg->u.signed_data.info->cSignerInfo)
                SetLastError(CRYPT_E_INVALID_INDEX);
            else
                ret = CRYPT_CopyCMSSignerInfo(pvData, pcbData,
                 &msg->u.signed_data.info->rgSignerInfo[dwIndex]);
        }
        else
            SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        break;
    default:
        FIXME("unimplemented for %d\n", dwParamType);
        SetLastError(CRYPT_E_INVALID_MSG_TYPE);
    }
    return ret;
}
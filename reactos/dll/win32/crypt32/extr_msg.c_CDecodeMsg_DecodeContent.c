#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_13__ {int type; TYPE_1__ msg_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  Content; int /*<<< orphan*/  pszObjId; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CRYPT_DER_BLOB ;
typedef  TYPE_2__ CRYPT_CONTENT_INFO ;
typedef  TYPE_3__ CDecodeMsg ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CDecodeMsg_DecodeDataContent (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CDecodeMsg_DecodeEnvelopedContent (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CDecodeMsg_DecodeHashedContent (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CDecodeMsg_DecodeSignedContent (TYPE_3__*,int /*<<< orphan*/  const*) ; 
#define  CMSG_DATA 131 
#define  CMSG_ENVELOPED 130 
#define  CMSG_HASHED 129 
#define  CMSG_SIGNED 128 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 int /*<<< orphan*/  CRYPT_E_INVALID_MSG_TYPE ; 
 int /*<<< orphan*/  CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**,int*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LocalFree (TYPE_2__*) ; 
 int /*<<< orphan*/  PKCS_CONTENT_INFO ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szOID_RSA_data ; 
 int /*<<< orphan*/  szOID_RSA_digestedData ; 
 int /*<<< orphan*/  szOID_RSA_envelopedData ; 
 int /*<<< orphan*/  szOID_RSA_signedData ; 

__attribute__((used)) static BOOL CDecodeMsg_DecodeContent(CDecodeMsg *msg, const CRYPT_DER_BLOB *blob,
 DWORD type)
{
    BOOL ret;

    switch (type)
    {
    case CMSG_DATA:
        if ((ret = CDecodeMsg_DecodeDataContent(msg, blob)))
            msg->type = CMSG_DATA;
        break;
    case CMSG_HASHED:
        if ((ret = CDecodeMsg_DecodeHashedContent(msg, blob)))
            msg->type = CMSG_HASHED;
        break;
    case CMSG_ENVELOPED:
        if ((ret = CDecodeMsg_DecodeEnvelopedContent(msg, blob)))
            msg->type = CMSG_ENVELOPED;
        break;
    case CMSG_SIGNED:
        if ((ret = CDecodeMsg_DecodeSignedContent(msg, blob)))
            msg->type = CMSG_SIGNED;
        break;
    default:
    {
        CRYPT_CONTENT_INFO *info;
        DWORD size;

        ret = CryptDecodeObjectEx(X509_ASN_ENCODING, PKCS_CONTENT_INFO,
         msg->msg_data.pbData, msg->msg_data.cbData, CRYPT_DECODE_ALLOC_FLAG,
         NULL, &info, &size);
        if (ret)
        {
            if (!strcmp(info->pszObjId, szOID_RSA_data))
                ret = CDecodeMsg_DecodeContent(msg, &info->Content, CMSG_DATA);
            else if (!strcmp(info->pszObjId, szOID_RSA_digestedData))
                ret = CDecodeMsg_DecodeContent(msg, &info->Content,
                 CMSG_HASHED);
            else if (!strcmp(info->pszObjId, szOID_RSA_envelopedData))
                ret = CDecodeMsg_DecodeContent(msg, &info->Content,
                 CMSG_ENVELOPED);
            else if (!strcmp(info->pszObjId, szOID_RSA_signedData))
                ret = CDecodeMsg_DecodeContent(msg, &info->Content,
                 CMSG_SIGNED);
            else
            {
                SetLastError(CRYPT_E_INVALID_MSG_TYPE);
                ret = FALSE;
            }
            LocalFree(info);
        }
    }
    }
    return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subjectInfo ;
typedef  int /*<<< orphan*/  sip ;
struct TYPE_10__ {int /*<<< orphan*/ * pbData; int /*<<< orphan*/  cbData; } ;
struct TYPE_9__ {int cbSize; scalar_t__ (* pfGet ) (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;void const* pwsFileName; scalar_t__ hFile; int /*<<< orphan*/ * pgSubjectType; } ;
typedef  TYPE_1__ SIP_SUBJECTINFO ;
typedef  TYPE_1__ SIP_DISPATCH_INFO ;
typedef  int /*<<< orphan*/  HCRYPTMSG ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_3__ CERT_BLOB ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED ; 
 scalar_t__ CERT_QUERY_CONTENT_PKCS7_SIGNED_EMBED ; 
 int /*<<< orphan*/  CERT_QUERY_FORMAT_FLAG_BINARY ; 
 int /*<<< orphan*/  CERT_QUERY_OBJECT_BLOB ; 
 scalar_t__ CERT_QUERY_OBJECT_FILE ; 
 scalar_t__ CRYPT_QueryMessageObject (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptMemAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ CryptSIPLoad (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ CryptSIPRetrieveSubjectGuid (void const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 scalar_t__ debugstr_w (void const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL CRYPT_QueryEmbeddedMessageObject(DWORD dwObjectType,
 const void *pvObject, DWORD dwExpectedContentTypeFlags,
 DWORD *pdwMsgAndCertEncodingType, DWORD *pdwContentType,
 HCERTSTORE *phCertStore, HCRYPTMSG *phMsg)
{
    HANDLE file;
    GUID subject;
    BOOL ret = FALSE;

    TRACE("%s\n", debugstr_w(pvObject));

    if (dwObjectType != CERT_QUERY_OBJECT_FILE)
    {
        WARN("don't know what to do for type %d embedded signed messages\n",
         dwObjectType);
        SetLastError(E_INVALIDARG);
        return FALSE;
    }
    file = CreateFileW(pvObject, GENERIC_READ, FILE_SHARE_READ,
     NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE)
    {
        ret = CryptSIPRetrieveSubjectGuid(pvObject, file, &subject);
        if (ret)
        {
            SIP_DISPATCH_INFO sip;

            memset(&sip, 0, sizeof(sip));
            sip.cbSize = sizeof(sip);
            ret = CryptSIPLoad(&subject, 0, &sip);
            if (ret)
            {
                SIP_SUBJECTINFO subjectInfo;
                CERT_BLOB blob;
                DWORD encodingType;

                memset(&subjectInfo, 0, sizeof(subjectInfo));
                subjectInfo.cbSize = sizeof(subjectInfo);
                subjectInfo.pgSubjectType = &subject;
                subjectInfo.hFile = file;
                subjectInfo.pwsFileName = pvObject;
                ret = sip.pfGet(&subjectInfo, &encodingType, 0, &blob.cbData,
                 NULL);
                if (ret)
                {
                    blob.pbData = CryptMemAlloc(blob.cbData);
                    if (blob.pbData)
                    {
                        ret = sip.pfGet(&subjectInfo, &encodingType, 0,
                         &blob.cbData, blob.pbData);
                        if (ret)
                        {
                            ret = CRYPT_QueryMessageObject(
                             CERT_QUERY_OBJECT_BLOB, &blob,
                             CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED,
                             CERT_QUERY_FORMAT_FLAG_BINARY,
                             pdwMsgAndCertEncodingType, NULL, NULL,
                             phCertStore, phMsg);
                            if (ret && pdwContentType)
                                *pdwContentType = CERT_QUERY_CONTENT_PKCS7_SIGNED_EMBED;
                        }
                        CryptMemFree(blob.pbData);
                    }
                    else
                    {
                        SetLastError(ERROR_OUTOFMEMORY);
                        ret = FALSE;
                    }
                }
            }
        }
        CloseHandle(file);
    }
    TRACE("returning %d\n", ret);
    return ret;
}
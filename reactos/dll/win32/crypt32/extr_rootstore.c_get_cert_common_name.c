#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_10__ {TYPE_1__* pCertInfo; } ;
struct TYPE_9__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  dwValueType; } ;
struct TYPE_8__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_7__ {TYPE_2__ Subject; } ;
typedef  TYPE_3__* PCERT_RDN_ATTR ;
typedef  TYPE_4__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CERT_NAME_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CRYPT_DECODE_ALLOC_FLAG ; 
 int CRYPT_DECODE_NOCOPY_FLAG ; 
 TYPE_3__* CertFindRDNAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertRDNValueToStrA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_NAME ; 
 int /*<<< orphan*/  szOID_COMMON_NAME ; 

__attribute__((used)) static const char *get_cert_common_name(PCCERT_CONTEXT cert)
{
    static char buf[1024];
    const char *name = NULL;
    CERT_NAME_INFO *nameInfo;
    DWORD size;
    BOOL ret = CryptDecodeObjectEx(X509_ASN_ENCODING, X509_NAME,
     cert->pCertInfo->Subject.pbData, cert->pCertInfo->Subject.cbData,
     CRYPT_DECODE_NOCOPY_FLAG | CRYPT_DECODE_ALLOC_FLAG, NULL, &nameInfo,
     &size);

    if (ret)
    {
        PCERT_RDN_ATTR commonName = CertFindRDNAttr(szOID_COMMON_NAME,
         nameInfo);

        if (commonName)
        {
            CertRDNValueToStrA(commonName->dwValueType,
             &commonName->Value, buf, sizeof(buf));
            name = buf;
        }
        LocalFree(nameInfo);
    }
    return name;
}
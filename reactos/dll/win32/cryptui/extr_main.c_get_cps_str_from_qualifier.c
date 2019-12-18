#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  dwValueType; } ;
struct TYPE_6__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int DWORD ;
typedef  TYPE_1__ CRYPT_OBJID_BLOB ;
typedef  TYPE_2__ CERT_NAME_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 int CertRDNValueToStrW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (TYPE_2__*) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_NAME_VALUE ; 

__attribute__((used)) static WCHAR *get_cps_str_from_qualifier(const CRYPT_OBJID_BLOB *qualifier)
{
    LPWSTR qualifierStr = NULL;
    CERT_NAME_VALUE *qualifierValue;
    DWORD size;

    if (CryptDecodeObjectEx(X509_ASN_ENCODING, X509_NAME_VALUE,
     qualifier->pbData, qualifier->cbData, CRYPT_DECODE_ALLOC_FLAG, NULL,
     &qualifierValue, &size))
    {
        size = CertRDNValueToStrW(qualifierValue->dwValueType,
         &qualifierValue->Value, NULL, 0);
        qualifierStr = HeapAlloc(GetProcessHeap(), 0, size * sizeof(WCHAR));
        if (qualifierStr)
            CertRDNValueToStrW(qualifierValue->dwValueType,
             &qualifierValue->Value, qualifierStr, size);
        LocalFree(qualifierValue);
    }
    return qualifierStr;
}
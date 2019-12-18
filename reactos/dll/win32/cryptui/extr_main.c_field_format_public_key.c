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
typedef  int /*<<< orphan*/  __ms_va_list ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int cbData; } ;
struct TYPE_9__ {int /*<<< orphan*/  pszObjId; } ;
struct TYPE_14__ {TYPE_2__ PublicKey; TYPE_1__ Algorithm; } ;
struct TYPE_13__ {TYPE_3__* pCertInfo; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pwszName; } ;
struct TYPE_11__ {TYPE_8__ SubjectPublicKeyInfo; } ;
typedef  TYPE_4__* PCCRYPT_OID_INFO ;
typedef  TYPE_5__* PCCERT_CONTEXT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPT_OID_INFO_OID_KEY ; 
 scalar_t__ CertGetPublicKeyLength (int /*<<< orphan*/ ,TYPE_8__*) ; 
 TYPE_4__* CryptFindOIDInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FORMAT_MESSAGE_ARGUMENT_ARRAY ; 
 int FORMAT_MESSAGE_FROM_STRING ; 
 int /*<<< orphan*/  FormatMessageW (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDS_FIELD_PUBLIC_KEY_FORMAT ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_STRING_LEN ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  hInstance ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *field_format_public_key(PCCERT_CONTEXT cert)
{
    PCCRYPT_OID_INFO oidInfo;
    WCHAR *buf = NULL;

    oidInfo = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY,
     cert->pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId, 0);
    if (oidInfo)
    {
        WCHAR fmt[MAX_STRING_LEN];

        if (LoadStringW(hInstance, IDS_FIELD_PUBLIC_KEY_FORMAT, fmt, ARRAY_SIZE(fmt)))
        {
            DWORD len;

            /* Allocate the output buffer.  Use the number of bytes in the
             * public key as a conservative (high) estimate for the number of
             * digits in its output.
             * The output is of the form (in English)
             * "<public key algorithm> (<public key bit length> bits)".
             * Ordinarily having two positional parameters in a string is not a
             * good idea, but as this isn't a sentence fragment, it shouldn't
             * be word-order dependent.
             */
            len = lstrlenW(fmt) + lstrlenW(oidInfo->pwszName) +
                cert->pCertInfo->SubjectPublicKeyInfo.PublicKey.cbData * 8;
            buf = HeapAlloc(GetProcessHeap(), 0, len * sizeof(*buf));
            if (buf)
            {
                DWORD_PTR args[2];
                args[0] = (DWORD_PTR)oidInfo->pwszName;
                args[1] = CertGetPublicKeyLength(X509_ASN_ENCODING,
                              &cert->pCertInfo->SubjectPublicKeyInfo);
                FormatMessageW(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ARGUMENT_ARRAY,
                               fmt, 0, 0, buf, len, (__ms_va_list*)args);
            }
        }
    }
    return buf;
}
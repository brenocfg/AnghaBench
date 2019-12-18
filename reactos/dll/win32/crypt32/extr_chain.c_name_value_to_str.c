#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CERT_NAME_BLOB ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_SIMPLE_NAME_STR ; 
 int /*<<< orphan*/ * CryptMemAlloc (int) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int cert_name_to_str_with_indent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static LPWSTR name_value_to_str(const CERT_NAME_BLOB *name)
{
    DWORD len = cert_name_to_str_with_indent(X509_ASN_ENCODING, 0, name,
     CERT_SIMPLE_NAME_STR, NULL, 0);
    LPWSTR str = NULL;

    if (len)
    {
        str = CryptMemAlloc(len * sizeof(WCHAR));
        if (str)
            cert_name_to_str_with_indent(X509_ASN_ENCODING, 0, name,
             CERT_SIMPLE_NAME_STR, str, len);
    }
    return str;
}
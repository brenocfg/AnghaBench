#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int cbData; int /*<<< orphan*/ * pbData; } ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ CRYPT_DATA_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CertSetCertificateContextProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int lstrlenW (scalar_t__*) ; 

__attribute__((used)) static void set_cert_string_property(PCCERT_CONTEXT cert, DWORD prop,
 LPWSTR str)
{
    if (str && *str)
    {
        CRYPT_DATA_BLOB blob;

        blob.pbData = (BYTE *)str;
        blob.cbData = (lstrlenW(str) + 1) * sizeof(WCHAR);
        CertSetCertificateContextProperty(cert, prop, 0, &blob);
    }
    else
        CertSetCertificateContextProperty(cert, prop, 0, NULL);
}
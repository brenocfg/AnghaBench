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
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 
 scalar_t__ i2a_ASN1_STRING (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2r_ocsp_nonce(const X509V3_EXT_METHOD *method, void *nonce,
                          BIO *out, int indent)
{
    if (BIO_printf(out, "%*s", indent, "") <= 0)
        return 0;
    if (i2a_ASN1_STRING(out, nonce, V_ASN1_OCTET_STRING) <= 0)
        return 0;
    return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
struct TYPE_5__ {int /*<<< orphan*/  location; int /*<<< orphan*/  method; } ;
struct TYPE_4__ {int /*<<< orphan*/  locator; int /*<<< orphan*/  issuer; } ;
typedef  TYPE_1__ OCSP_SERVICELOC ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_2__ ACCESS_DESCRIPTION ;

/* Variables and functions */
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,int,char*) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ GENERAL_NAME_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ X509_NAME_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XN_FLAG_ONELINE ; 
 scalar_t__ i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sk_ACCESS_DESCRIPTION_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_ACCESS_DESCRIPTION_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2r_ocsp_serviceloc(const X509V3_EXT_METHOD *method, void *in,
                               BIO *bp, int ind)
{
    int i;
    OCSP_SERVICELOC *a = in;
    ACCESS_DESCRIPTION *ad;

    if (BIO_printf(bp, "%*sIssuer: ", ind, "") <= 0)
        goto err;
    if (X509_NAME_print_ex(bp, a->issuer, 0, XN_FLAG_ONELINE) <= 0)
        goto err;
    for (i = 0; i < sk_ACCESS_DESCRIPTION_num(a->locator); i++) {
        ad = sk_ACCESS_DESCRIPTION_value(a->locator, i);
        if (BIO_printf(bp, "\n%*s", (2 * ind), "") <= 0)
            goto err;
        if (i2a_ASN1_OBJECT(bp, ad->method) <= 0)
            goto err;
        if (BIO_puts(bp, " - ") <= 0)
            goto err;
        if (GENERAL_NAME_print(bp, ad->location) <= 0)
            goto err;
    }
    return 1;
 err:
    return 0;
}
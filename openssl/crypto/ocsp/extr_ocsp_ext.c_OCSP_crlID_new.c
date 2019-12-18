#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_EXTENSION ;
struct TYPE_5__ {int /*<<< orphan*/ * crlTime; int /*<<< orphan*/ * crlNum; int /*<<< orphan*/ * crlUrl; } ;
typedef  TYPE_1__ OCSP_CRLID ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_GENERALIZEDTIME_new () ; 
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_set_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ASN1_IA5STRING_new () ; 
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  NID_id_pkix_OCSP_CrlID ; 
 int /*<<< orphan*/  OCSP_CRLID_free (TYPE_1__*) ; 
 TYPE_1__* OCSP_CRLID_new () ; 
 int /*<<< orphan*/ * X509V3_EXT_i2d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

X509_EXTENSION *OCSP_crlID_new(const char *url, long *n, char *tim)
{
    X509_EXTENSION *x = NULL;
    OCSP_CRLID *cid = NULL;

    if ((cid = OCSP_CRLID_new()) == NULL)
        goto err;
    if (url) {
        if ((cid->crlUrl = ASN1_IA5STRING_new()) == NULL)
            goto err;
        if (!(ASN1_STRING_set(cid->crlUrl, url, -1)))
            goto err;
    }
    if (n) {
        if ((cid->crlNum = ASN1_INTEGER_new()) == NULL)
            goto err;
        if (!(ASN1_INTEGER_set(cid->crlNum, *n)))
            goto err;
    }
    if (tim) {
        if ((cid->crlTime = ASN1_GENERALIZEDTIME_new()) == NULL)
            goto err;
        if (!(ASN1_GENERALIZEDTIME_set_string(cid->crlTime, tim)))
            goto err;
    }
    x = X509V3_EXT_i2d(NID_id_pkix_OCSP_CrlID, 0, cid);
 err:
    OCSP_CRLID_free(cid);
    return x;
}
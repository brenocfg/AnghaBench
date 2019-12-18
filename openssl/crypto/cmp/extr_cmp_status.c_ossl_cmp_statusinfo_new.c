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
struct TYPE_5__ {int /*<<< orphan*/ * failInfo; int /*<<< orphan*/ * statusString; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ OSSL_CMP_PKISI ;
typedef  int /*<<< orphan*/  ASN1_UTF8STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_BIT_STRING_new () ; 
 int /*<<< orphan*/  ASN1_BIT_STRING_set_bit (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ASN1_UTF8STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_UTF8STRING_new () ; 
 int OSSL_CMP_PKIFAILUREINFO_MAX ; 
 int /*<<< orphan*/  OSSL_CMP_PKISI_free (TYPE_1__*) ; 
 TYPE_1__* OSSL_CMP_PKISI_new () ; 
 int /*<<< orphan*/ * sk_ASN1_UTF8STRING_new_null () ; 
 int /*<<< orphan*/  sk_ASN1_UTF8STRING_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

OSSL_CMP_PKISI *ossl_cmp_statusinfo_new(int status, int fail_info,
                                        const char *text)
{
    OSSL_CMP_PKISI *si = OSSL_CMP_PKISI_new();
    ASN1_UTF8STRING *utf8_text = NULL;
    int failure;

    if (si == NULL)
        goto err;
    if (!ASN1_INTEGER_set(si->status, status))
        goto err;

    if (text != NULL) {
        if ((utf8_text = ASN1_UTF8STRING_new()) == NULL
                || !ASN1_STRING_set(utf8_text, text, -1))
            goto err;
        if ((si->statusString = sk_ASN1_UTF8STRING_new_null()) == NULL)
            goto err;
        if (!sk_ASN1_UTF8STRING_push(si->statusString, utf8_text))
            goto err;
        /* Ownership is lost. */
        utf8_text = NULL;
    }

    for (failure = 0; failure <= OSSL_CMP_PKIFAILUREINFO_MAX; failure++) {
        if ((fail_info & (1 << failure)) != 0) {
            if (si->failInfo == NULL
                    && (si->failInfo = ASN1_BIT_STRING_new()) == NULL)
                goto err;
            if (!ASN1_BIT_STRING_set_bit(si->failInfo, failure, 1))
                goto err;
        }
    }
    return si;

 err:
    OSSL_CMP_PKISI_free(si);
    ASN1_UTF8STRING_free(utf8_text);
    return NULL;
}
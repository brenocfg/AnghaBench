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
typedef  int /*<<< orphan*/  OSSL_CMP_PKIFREETEXT ;
typedef  int /*<<< orphan*/  ASN1_UTF8STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ASN1_UTF8STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_UTF8STRING_new () ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  sk_ASN1_UTF8STRING_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ossl_cmp_pkifreetext_push_str(OSSL_CMP_PKIFREETEXT *ft, const char *text)
{
    ASN1_UTF8STRING *utf8string;

    if (!ossl_assert(ft != NULL && text != NULL))
        return 0;
    if ((utf8string = ASN1_UTF8STRING_new()) == NULL)
        return 0;
    if (!ASN1_STRING_set(utf8string, text, -1))
        goto err;
    if (!sk_ASN1_UTF8STRING_push(ft, utf8string))
        goto err;
    return 1;

 err:
    ASN1_UTF8STRING_free(utf8string);
    return 0;
}
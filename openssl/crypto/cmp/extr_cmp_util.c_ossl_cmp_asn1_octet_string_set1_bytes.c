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
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ossl_cmp_asn1_octet_string_set1_bytes(ASN1_OCTET_STRING **tgt,
                                          const unsigned char *bytes, int len)
{
    ASN1_OCTET_STRING *new = NULL;

    if (tgt == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    if (bytes != NULL) {
        if ((new =  ASN1_OCTET_STRING_new()) == NULL
                || !(ASN1_OCTET_STRING_set(new, bytes, len))) {
            ASN1_OCTET_STRING_free(new);
            return 0;
        }
    }

    ASN1_OCTET_STRING_free(*tgt);
    *tgt = new;
    return 1;
}
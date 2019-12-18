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
typedef  int /*<<< orphan*/  const ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  const* ASN1_OCTET_STRING_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ossl_cmp_asn1_octet_string_set1(ASN1_OCTET_STRING **tgt,
                                    const ASN1_OCTET_STRING *src)
{
    if (tgt == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    if (*tgt == src) /* self-assignment */
        return 1;
    ASN1_OCTET_STRING_free(*tgt);

    if (src != NULL) {
        if ((*tgt = ASN1_OCTET_STRING_dup(src)) == NULL)
            return 0;
    } else {
        *tgt = NULL;
    }

    return 1;
}
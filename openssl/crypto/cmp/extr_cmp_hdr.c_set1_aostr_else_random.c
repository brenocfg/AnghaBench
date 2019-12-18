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
 int /*<<< orphan*/  CMP_R_FAILURE_OBTAINING_RANDOM ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 scalar_t__ RAND_bytes (unsigned char*,size_t) ; 
 int ossl_cmp_asn1_octet_string_set1 (int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int ossl_cmp_asn1_octet_string_set1_bytes (int /*<<< orphan*/ **,unsigned char*,size_t) ; 

__attribute__((used)) static int set1_aostr_else_random(ASN1_OCTET_STRING **tgt,
                                  const ASN1_OCTET_STRING *src, size_t len)
{
    unsigned char *bytes = NULL;
    int res = 0;

    if (src == NULL) { /* generate a random value if src == NULL */
        if ((bytes = OPENSSL_malloc(len)) == NULL)
            goto err;
        if (RAND_bytes(bytes, len) <= 0) {
            CMPerr(0, CMP_R_FAILURE_OBTAINING_RANDOM);
            goto err;
        }
        res = ossl_cmp_asn1_octet_string_set1_bytes(tgt, bytes, len);
    } else {
        res = ossl_cmp_asn1_octet_string_set1(tgt, src);
    }

 err:
    OPENSSL_free(bytes);
    return res;
}
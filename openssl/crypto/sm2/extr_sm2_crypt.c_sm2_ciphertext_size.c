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
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int ASN1_object_size (int,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/  const*) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  V_ASN1_INTEGER ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 size_t ec_field_size (int /*<<< orphan*/ ) ; 

int sm2_ciphertext_size(const EC_KEY *key, const EVP_MD *digest, size_t msg_len,
                        size_t *ct_size)
{
    const size_t field_size = ec_field_size(EC_KEY_get0_group(key));
    const int md_size = EVP_MD_size(digest);
    size_t sz;

    if (field_size == 0 || md_size < 0)
        return 0;

    /* Integer and string are simple type; set constructed = 0, means primitive and definite length encoding. */
    sz = 2 * ASN1_object_size(0, field_size + 1, V_ASN1_INTEGER)
         + ASN1_object_size(0, md_size, V_ASN1_OCTET_STRING)
         + ASN1_object_size(0, msg_len, V_ASN1_OCTET_STRING);
    /* Sequence is structured type; set constructed = 1, means constructed and definite length encoding. */
    *ct_size = ASN1_object_size(1, sz, V_ASN1_SEQUENCE);

    return 1;
}
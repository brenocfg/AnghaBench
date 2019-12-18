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
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int ASN1_TYPE_get_int_octetstring (int /*<<< orphan*/ *,long*,unsigned char*,unsigned int) ; 
 scalar_t__ EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 unsigned int EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_set_key_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_CTRL_SET_RC2_KEY_BITS ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int EVP_MAX_IV_LENGTH ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int rc2_magic_to_meth (int) ; 

__attribute__((used)) static int rc2_get_asn1_type_and_iv(EVP_CIPHER_CTX *c, ASN1_TYPE *type)
{
    long num = 0;
    int i = 0;
    int key_bits;
    unsigned int l;
    unsigned char iv[EVP_MAX_IV_LENGTH];

    if (type != NULL) {
        l = EVP_CIPHER_CTX_iv_length(c);
        OPENSSL_assert(l <= sizeof(iv));
        i = ASN1_TYPE_get_int_octetstring(type, &num, iv, l);
        if (i != (int)l)
            return -1;
        key_bits = rc2_magic_to_meth((int)num);
        if (!key_bits)
            return -1;
        if (i > 0 && !EVP_CipherInit_ex(c, NULL, NULL, NULL, iv, -1))
            return -1;
        if (EVP_CIPHER_CTX_ctrl(c, EVP_CTRL_SET_RC2_KEY_BITS, key_bits,
                                NULL) <= 0
                || EVP_CIPHER_CTX_set_key_length(c, key_bits / 8) <= 0)
            return -1;
    }
    return i;
}
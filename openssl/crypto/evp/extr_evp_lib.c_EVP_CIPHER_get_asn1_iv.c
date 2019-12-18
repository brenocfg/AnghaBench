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
 int ASN1_TYPE_get_octetstring (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 unsigned int EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int EVP_MAX_IV_LENGTH ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

int EVP_CIPHER_get_asn1_iv(EVP_CIPHER_CTX *ctx, ASN1_TYPE *type)
{
    int i = 0;
    unsigned int l;

    if (type != NULL) {
        unsigned char iv[EVP_MAX_IV_LENGTH];

        l = EVP_CIPHER_CTX_iv_length(ctx);
        if (!ossl_assert(l <= sizeof(iv)))
            return -1;
        i = ASN1_TYPE_get_octetstring(type, iv, l);
        if (i != (int)l)
            return -1;

        if (!EVP_CipherInit_ex(ctx, NULL, NULL, NULL, iv, -1))
            return -1;
    }
    return i;
}
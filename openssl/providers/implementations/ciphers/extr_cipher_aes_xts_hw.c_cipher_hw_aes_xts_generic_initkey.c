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
typedef  int /*<<< orphan*/  PROV_CIPHER_CTX ;
typedef  int /*<<< orphan*/  PROV_AES_XTS_CTX ;
typedef  int /*<<< orphan*/ * OSSL_xts_stream_fn ;

/* Variables and functions */
 int /*<<< orphan*/  AES_decrypt ; 
 int /*<<< orphan*/  AES_encrypt ; 
 int /*<<< orphan*/  AES_set_decrypt_key ; 
 int /*<<< orphan*/  AES_set_encrypt_key ; 
 int /*<<< orphan*/ * AES_xts_decrypt ; 
 int /*<<< orphan*/ * AES_xts_encrypt ; 
 scalar_t__ BSAES_CAPABLE ; 
 scalar_t__ HWAES_CAPABLE ; 
 int /*<<< orphan*/  HWAES_decrypt ; 
 int /*<<< orphan*/  HWAES_encrypt ; 
 int /*<<< orphan*/  HWAES_set_decrypt_key ; 
 int /*<<< orphan*/  HWAES_set_encrypt_key ; 
 int /*<<< orphan*/ * HWAES_xts_decrypt ; 
 int /*<<< orphan*/ * HWAES_xts_encrypt ; 
 scalar_t__ VPAES_CAPABLE ; 
 int /*<<< orphan*/  XTS_SET_KEY_FN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bsaes_xts_decrypt ; 
 int /*<<< orphan*/ * bsaes_xts_encrypt ; 
 int /*<<< orphan*/  vpaes_decrypt ; 
 int /*<<< orphan*/  vpaes_encrypt ; 
 int /*<<< orphan*/  vpaes_set_decrypt_key ; 
 int /*<<< orphan*/  vpaes_set_encrypt_key ; 

__attribute__((used)) static int cipher_hw_aes_xts_generic_initkey(PROV_CIPHER_CTX *ctx,
                                             const unsigned char *key,
                                             size_t keylen)
{
    PROV_AES_XTS_CTX *xctx = (PROV_AES_XTS_CTX *)ctx;
    OSSL_xts_stream_fn stream_enc = NULL;
    OSSL_xts_stream_fn stream_dec = NULL;

#ifdef AES_XTS_ASM
    stream_enc = AES_xts_encrypt;
    stream_dec = AES_xts_decrypt;
#endif /* AES_XTS_ASM */

#ifdef HWAES_CAPABLE
    if (HWAES_CAPABLE) {
# ifdef HWAES_xts_encrypt
        stream_enc = HWAES_xts_encrypt;
# endif /* HWAES_xts_encrypt */
# ifdef HWAES_xts_decrypt
        stream_dec = HWAES_xts_decrypt;
# endif /* HWAES_xts_decrypt */
        XTS_SET_KEY_FN(HWAES_set_encrypt_key, HWAES_set_decrypt_key,
                       HWAES_encrypt, HWAES_decrypt,
                       stream_enc, stream_dec);
    } else
#endif /* HWAES_CAPABLE */

#ifdef BSAES_CAPABLE
    if (BSAES_CAPABLE) {
        stream_enc = bsaes_xts_encrypt;
        stream_dec = bsaes_xts_decrypt;
    }
#endif /* BSAES_CAPABLE */

#ifdef VPAES_CAPABLE
    if (VPAES_CAPABLE) {
        XTS_SET_KEY_FN(vpaes_set_encrypt_key, vpaes_set_decrypt_key,
                       vpaes_encrypt, vpaes_decrypt, stream_enc, stream_dec);
    } else
#endif /* VPAES_CAPABLE */
    {
        XTS_SET_KEY_FN(AES_set_encrypt_key, AES_set_decrypt_key,
                       AES_encrypt, AES_decrypt, stream_enc, stream_dec);
    }
    return 1;
}
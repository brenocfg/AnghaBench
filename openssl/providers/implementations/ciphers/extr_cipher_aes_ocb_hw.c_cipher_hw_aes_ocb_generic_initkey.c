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
typedef  int /*<<< orphan*/  PROV_AES_OCB_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  AES_decrypt ; 
 int /*<<< orphan*/  AES_encrypt ; 
 int /*<<< orphan*/  AES_set_decrypt_key ; 
 int /*<<< orphan*/  AES_set_encrypt_key ; 
 scalar_t__ HWAES_CAPABLE ; 
 int /*<<< orphan*/  HWAES_decrypt ; 
 int /*<<< orphan*/  HWAES_encrypt ; 
 int /*<<< orphan*/ * HWAES_ocb_decrypt ; 
 int /*<<< orphan*/ * HWAES_ocb_encrypt ; 
 int /*<<< orphan*/  HWAES_set_decrypt_key ; 
 int /*<<< orphan*/  HWAES_set_encrypt_key ; 
 int /*<<< orphan*/  OCB_SET_KEY_FN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ VPAES_CAPABLE ; 
 int /*<<< orphan*/  vpaes_decrypt ; 
 int /*<<< orphan*/  vpaes_encrypt ; 
 int /*<<< orphan*/  vpaes_set_decrypt_key ; 
 int /*<<< orphan*/  vpaes_set_encrypt_key ; 

__attribute__((used)) static int cipher_hw_aes_ocb_generic_initkey(PROV_CIPHER_CTX *vctx,
                                             const unsigned char *key,
                                             size_t keylen)
{
    PROV_AES_OCB_CTX *ctx = (PROV_AES_OCB_CTX *)vctx;

/*
 * We set both the encrypt and decrypt key here because decrypt
 * needs both. (i.e- AAD uses encrypt).
 */
# ifdef HWAES_CAPABLE
    if (HWAES_CAPABLE) {
        OCB_SET_KEY_FN(HWAES_set_encrypt_key, HWAES_set_decrypt_key,
                       HWAES_encrypt, HWAES_decrypt,
                       HWAES_ocb_encrypt, HWAES_ocb_decrypt);
    } else
# endif
# ifdef VPAES_CAPABLE
    if (VPAES_CAPABLE) {
        OCB_SET_KEY_FN(vpaes_set_encrypt_key, vpaes_set_decrypt_key,
                       vpaes_encrypt, vpaes_decrypt, NULL, NULL);
    } else
# endif
    {
        OCB_SET_KEY_FN(AES_set_encrypt_key, AES_set_decrypt_key,
                       AES_encrypt, AES_decrypt, NULL, NULL);
    }
    return 1;
}
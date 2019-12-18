#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* ctr128_f ;
typedef  int /*<<< orphan*/ * cbc128_f ;
typedef  void* block128_f ;
struct TYPE_6__ {int /*<<< orphan*/  ks; } ;
struct TYPE_9__ {TYPE_1__ ks; } ;
struct TYPE_7__ {void* ctr; int /*<<< orphan*/ * cbc; } ;
struct TYPE_8__ {scalar_t__ mode; TYPE_2__ stream; void* block; int /*<<< orphan*/  enc; int /*<<< orphan*/ * ks; } ;
typedef  TYPE_3__ PROV_CIPHER_CTX ;
typedef  TYPE_4__ PROV_AES_CTX ;
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 scalar_t__ AES_cbc_encrypt ; 
 scalar_t__ AES_ctr32_encrypt ; 
 scalar_t__ AES_decrypt ; 
 scalar_t__ AES_encrypt ; 
 int AES_set_decrypt_key (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int AES_set_encrypt_key (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ BSAES_CAPABLE ; 
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_CIPH_CBC_MODE ; 
 scalar_t__ EVP_CIPH_CTR_MODE ; 
 scalar_t__ EVP_CIPH_ECB_MODE ; 
 scalar_t__ HWAES_CAPABLE ; 
 scalar_t__ HWAES_cbc_encrypt ; 
 scalar_t__ HWAES_ctr32_encrypt_blocks ; 
 scalar_t__ HWAES_decrypt ; 
 scalar_t__ HWAES_encrypt ; 
 int HWAES_set_decrypt_key (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int HWAES_set_encrypt_key (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROV_R_AES_KEY_SETUP_FAILED ; 
 scalar_t__ VPAES_CAPABLE ; 
 scalar_t__ bsaes_cbc_encrypt ; 
 scalar_t__ bsaes_ctr32_encrypt_blocks ; 
 scalar_t__ vpaes_cbc_encrypt ; 
 scalar_t__ vpaes_decrypt ; 
 scalar_t__ vpaes_encrypt ; 
 int vpaes_set_decrypt_key (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int vpaes_set_encrypt_key (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cipher_hw_aes_initkey(PROV_CIPHER_CTX *dat,
                                 const unsigned char *key, size_t keylen)
{
    int ret;
    PROV_AES_CTX *adat = (PROV_AES_CTX *)dat;
    AES_KEY *ks = &adat->ks.ks;

    dat->ks = ks;

    if ((dat->mode == EVP_CIPH_ECB_MODE || dat->mode == EVP_CIPH_CBC_MODE)
        && !dat->enc) {
#ifdef HWAES_CAPABLE
        if (HWAES_CAPABLE) {
            ret = HWAES_set_decrypt_key(key, keylen * 8, ks);
            dat->block = (block128_f)HWAES_decrypt;
            dat->stream.cbc = NULL;
# ifdef HWAES_cbc_encrypt
            if (dat->mode == EVP_CIPH_CBC_MODE)
                dat->stream.cbc = (cbc128_f)HWAES_cbc_encrypt;
# endif
        } else
#endif
#ifdef BSAES_CAPABLE
        if (BSAES_CAPABLE && dat->mode == EVP_CIPH_CBC_MODE) {
            ret = AES_set_decrypt_key(key, keylen * 8, ks);
            dat->block = (block128_f)AES_decrypt;
            dat->stream.cbc = (cbc128_f)bsaes_cbc_encrypt;
        } else
#endif
#ifdef VPAES_CAPABLE
        if (VPAES_CAPABLE) {
            ret = vpaes_set_decrypt_key(key, keylen * 8, ks);
            dat->block = (block128_f)vpaes_decrypt;
            dat->stream.cbc = (dat->mode == EVP_CIPH_CBC_MODE)
                              ?(cbc128_f)vpaes_cbc_encrypt : NULL;
        } else
#endif
        {
            ret = AES_set_decrypt_key(key, keylen * 8, ks);
            dat->block = (block128_f)AES_decrypt;
            dat->stream.cbc = (dat->mode == EVP_CIPH_CBC_MODE)
                              ? (cbc128_f)AES_cbc_encrypt : NULL;
        }
    } else
#ifdef HWAES_CAPABLE
    if (HWAES_CAPABLE) {
        ret = HWAES_set_encrypt_key(key, keylen * 8, ks);
        dat->block = (block128_f)HWAES_encrypt;
        dat->stream.cbc = NULL;
# ifdef HWAES_cbc_encrypt
        if (dat->mode == EVP_CIPH_CBC_MODE)
            dat->stream.cbc = (cbc128_f)HWAES_cbc_encrypt;
        else
# endif
# ifdef HWAES_ctr32_encrypt_blocks
        if (dat->mode == EVP_CIPH_CTR_MODE)
            dat->stream.ctr = (ctr128_f)HWAES_ctr32_encrypt_blocks;
        else
# endif
            (void)0;            /* terminate potentially open 'else' */
    } else
#endif
#ifdef BSAES_CAPABLE
    if (BSAES_CAPABLE && dat->mode == EVP_CIPH_CTR_MODE) {
        ret = AES_set_encrypt_key(key, keylen * 8, ks);
        dat->block = (block128_f)AES_encrypt;
        dat->stream.ctr = (ctr128_f)bsaes_ctr32_encrypt_blocks;
    } else
#endif
#ifdef VPAES_CAPABLE
    if (VPAES_CAPABLE) {
        ret = vpaes_set_encrypt_key(key, keylen * 8, ks);
        dat->block = (block128_f)vpaes_encrypt;
        dat->stream.cbc = (dat->mode == EVP_CIPH_CBC_MODE)
                          ? (cbc128_f)vpaes_cbc_encrypt : NULL;
    } else
#endif
    {
        ret = AES_set_encrypt_key(key, keylen * 8, ks);
        dat->block = (block128_f)AES_encrypt;
        dat->stream.cbc = (dat->mode == EVP_CIPH_CBC_MODE)
                          ? (cbc128_f)AES_cbc_encrypt : NULL;
#ifdef AES_CTR_ASM
        if (dat->mode == EVP_CIPH_CTR_MODE)
            dat->stream.ctr = (ctr128_f)AES_ctr32_encrypt;
#endif
    }

    if (ret < 0) {
        ERR_raise(ERR_LIB_PROV, PROV_R_AES_KEY_SETUP_FAILED);
        return 0;
    }

    return 1;
}
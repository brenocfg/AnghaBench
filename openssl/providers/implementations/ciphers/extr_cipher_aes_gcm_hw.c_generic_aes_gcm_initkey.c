#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ks; } ;
struct TYPE_7__ {TYPE_1__ ks; } ;
struct TYPE_6__ {int key_set; } ;
typedef  TYPE_2__ PROV_GCM_CTX ;
typedef  TYPE_3__ PROV_AES_GCM_CTX ;
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 int /*<<< orphan*/ * AES_ctr32_encrypt ; 
 int /*<<< orphan*/  AES_encrypt ; 
 int /*<<< orphan*/  AES_set_encrypt_key ; 
 scalar_t__ BSAES_CAPABLE ; 
 int /*<<< orphan*/  GCM_HW_SET_KEY_CTR_FN (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HWAES_CAPABLE ; 
 int /*<<< orphan*/ * HWAES_ctr32_encrypt_blocks ; 
 int /*<<< orphan*/  HWAES_encrypt ; 
 int /*<<< orphan*/  HWAES_set_encrypt_key ; 
 scalar_t__ VPAES_CAPABLE ; 
 int /*<<< orphan*/ * bsaes_ctr32_encrypt_blocks ; 
 int /*<<< orphan*/  vpaes_encrypt ; 
 int /*<<< orphan*/  vpaes_set_encrypt_key ; 

__attribute__((used)) static int generic_aes_gcm_initkey(PROV_GCM_CTX *ctx, const unsigned char *key,
                                   size_t keylen)
{
    PROV_AES_GCM_CTX *actx = (PROV_AES_GCM_CTX *)ctx;
    AES_KEY *ks = &actx->ks.ks;

# ifdef HWAES_CAPABLE
    if (HWAES_CAPABLE) {
#  ifdef HWAES_ctr32_encrypt_blocks
        GCM_HW_SET_KEY_CTR_FN(ks, HWAES_set_encrypt_key, HWAES_encrypt,
                              HWAES_ctr32_encrypt_blocks);
#  else
        GCM_HW_SET_KEY_CTR_FN(ks, HWAES_set_encrypt_key, HWAES_encrypt, NULL);
#  endif /* HWAES_ctr32_encrypt_blocks */
    } else
# endif /* HWAES_CAPABLE */

# ifdef BSAES_CAPABLE
    if (BSAES_CAPABLE) {
        GCM_HW_SET_KEY_CTR_FN(ks, AES_set_encrypt_key, AES_encrypt,
                              bsaes_ctr32_encrypt_blocks);
    } else
# endif /* BSAES_CAPABLE */

# ifdef VPAES_CAPABLE
    if (VPAES_CAPABLE) {
        GCM_HW_SET_KEY_CTR_FN(ks, vpaes_set_encrypt_key, vpaes_encrypt, NULL);
    } else
# endif /* VPAES_CAPABLE */

    {
# ifdef AES_CTR_ASM
        GCM_HW_SET_KEY_CTR_FN(ks, AES_set_encrypt_key, AES_encrypt,
                              AES_ctr32_encrypt);
# else
        GCM_HW_SET_KEY_CTR_FN(ks, AES_set_encrypt_key, AES_encrypt, NULL);
# endif /* AES_CTR_ASM */
    }
    ctx->key_set = 1;
    return 1;
}
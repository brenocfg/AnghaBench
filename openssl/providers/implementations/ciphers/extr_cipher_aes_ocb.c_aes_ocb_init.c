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
struct TYPE_7__ {int enc; size_t ivlen; size_t keylen; TYPE_1__* hw; } ;
struct TYPE_6__ {TYPE_3__ base; int /*<<< orphan*/  iv_state; } ;
struct TYPE_5__ {int (* init ) (TYPE_3__*,unsigned char const*,size_t) ;} ;
typedef  TYPE_2__ PROV_AES_OCB_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IV_STATE_BUFFERED ; 
 size_t OCB_MAX_IV_LEN ; 
 size_t OCB_MIN_IV_LEN ; 
 int /*<<< orphan*/  PROV_R_INVALID_IV_LENGTH ; 
 int /*<<< orphan*/  PROV_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  cipher_generic_initiv (TYPE_3__*,unsigned char const*,size_t) ; 
 int stub1 (TYPE_3__*,unsigned char const*,size_t) ; 

__attribute__((used)) static int aes_ocb_init(void *vctx, const unsigned char *key, size_t keylen,
                        const unsigned char *iv, size_t ivlen, int enc)
{
   PROV_AES_OCB_CTX *ctx = (PROV_AES_OCB_CTX *)vctx;

   ctx->base.enc = enc;

   if (iv != NULL) {
       if (ivlen != ctx->base.ivlen) {
           /* IV len must be 1 to 15 */
           if (ivlen < OCB_MIN_IV_LEN || ivlen > OCB_MAX_IV_LEN) {
               ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_IV_LENGTH);
               return 0;
           }
           ctx->base.ivlen = ivlen;
       }
       if (!cipher_generic_initiv(&ctx->base, iv, ivlen))
           return 0;
       ctx->iv_state = IV_STATE_BUFFERED;
   }
   if (key != NULL) {
       if (keylen != ctx->base.keylen) {
           ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_KEY_LENGTH);
           return 0;
       }
       return ctx->base.hw->init(&ctx->base, key, keylen);
   }
   return 1;
}
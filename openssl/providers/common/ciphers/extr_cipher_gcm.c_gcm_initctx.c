#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pad; size_t ivlen_min; size_t keylen; int /*<<< orphan*/  libctx; int /*<<< orphan*/  const* hw; scalar_t__ ivlen; void* tls_aad_len; void* taglen; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  PROV_GCM_HW ;
typedef  TYPE_1__ PROV_GCM_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPH_GCM_MODE ; 
 scalar_t__ EVP_GCM_TLS_EXPLICIT_IV_LEN ; 
 scalar_t__ EVP_GCM_TLS_FIXED_IV_LEN ; 
 int /*<<< orphan*/  PROV_LIBRARY_CONTEXT_OF (void*) ; 
 void* UNINITIALISED_SIZET ; 

void gcm_initctx(void *provctx, PROV_GCM_CTX *ctx, size_t keybits,
                 const PROV_GCM_HW *hw, size_t ivlen_min)
{
    ctx->pad = 1;
    ctx->mode = EVP_CIPH_GCM_MODE;
    ctx->taglen = UNINITIALISED_SIZET;
    ctx->tls_aad_len = UNINITIALISED_SIZET;
    ctx->ivlen_min = ivlen_min;
    ctx->ivlen = (EVP_GCM_TLS_FIXED_IV_LEN + EVP_GCM_TLS_EXPLICIT_IV_LEN);
    ctx->keylen = keybits / 8;
    ctx->hw = hw;
    ctx->libctx = PROV_LIBRARY_CONTEXT_OF(provctx);
}
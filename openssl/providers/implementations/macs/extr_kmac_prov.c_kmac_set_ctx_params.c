#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct kmac_data_st {int /*<<< orphan*/  custom_len; int /*<<< orphan*/  custom; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  out_len; int /*<<< orphan*/  xof_mode; int /*<<< orphan*/  digest; } ;
struct TYPE_7__ {int data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_block_size (int /*<<< orphan*/  const*) ; 
 int KMAC_MAX_CUSTOM ; 
 int KMAC_MAX_KEY ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_CUSTOM ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_SIZE ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_XOF ; 
 int /*<<< orphan*/  OSSL_PARAM_get_int (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_size_t (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_INVALID_CUSTOM_LENGTH ; 
 int /*<<< orphan*/  PROV_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  encode_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmac_bytepad_encode_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ossl_prov_digest_md (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kmac_set_ctx_params(void *vmacctx, const OSSL_PARAM *params)
{
    struct kmac_data_st *kctx = vmacctx;
    const OSSL_PARAM *p;
    const EVP_MD *digest = ossl_prov_digest_md(&kctx->digest);

    if ((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_XOF)) != NULL
        && !OSSL_PARAM_get_int(p, &kctx->xof_mode))
        return 0;
    if (((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_SIZE)) != NULL)
        && !OSSL_PARAM_get_size_t(p, &kctx->out_len))
        return 0;
    if ((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_KEY)) != NULL) {
        if (p->data_size < 4 || p->data_size > KMAC_MAX_KEY) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_KEY_LENGTH);
            return 0;
        }
        if (!kmac_bytepad_encode_key(kctx->key, &kctx->key_len,
                                     p->data, p->data_size,
                                     EVP_MD_block_size(digest)))
            return 0;
    }
    if ((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_CUSTOM))
        != NULL) {
        if (p->data_size > KMAC_MAX_CUSTOM) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_CUSTOM_LENGTH);
            return 0;
        }
        if (!encode_string(kctx->custom, &kctx->custom_len,
                           p->data, p->data_size))
            return 0;
    }
    return 1;
}
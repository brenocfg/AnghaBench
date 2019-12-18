#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct siphash_data_st {int /*<<< orphan*/  siphash; } ;
struct TYPE_6__ {scalar_t__ data_type; scalar_t__ data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_SIZE ; 
 scalar_t__ OSSL_PARAM_OCTET_STRING ; 
 int /*<<< orphan*/  OSSL_PARAM_get_size_t (TYPE_1__ const*,size_t*) ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ SIPHASH_KEY_SIZE ; 
 int /*<<< orphan*/  SipHash_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SipHash_set_hash_size (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int siphash_set_params(void *vmacctx, const OSSL_PARAM *params)
{
    struct siphash_data_st *ctx = vmacctx;
    const OSSL_PARAM *p = NULL;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_SIZE)) != NULL) {
        size_t size;

        if (!OSSL_PARAM_get_size_t(p, &size)
            || !SipHash_set_hash_size(&ctx->siphash, size))
            return 0;
    }
    if ((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_KEY)) != NULL)
        if (p->data_type != OSSL_PARAM_OCTET_STRING
            || p->data_size != SIPHASH_KEY_SIZE
            || !SipHash_Init(&ctx->siphash, p->data, 0, 0))
            return 0;
    return 1;
}
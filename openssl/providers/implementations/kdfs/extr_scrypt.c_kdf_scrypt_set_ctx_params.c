#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int N; int r; int p; int maxmem_bytes; int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  pass_len; int /*<<< orphan*/  pass; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ KDF_SCRYPT ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_KDF_PARAM_PASSWORD ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_MAXMEM ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_N ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_P ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_R ; 
 int /*<<< orphan*/  OSSL_PARAM_get_uint64 (int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate_const (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_two (int) ; 
 int /*<<< orphan*/  scrypt_set_membuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int kdf_scrypt_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    const OSSL_PARAM *p;
    KDF_SCRYPT *ctx = vctx;
    uint64_t u64_value;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_PASSWORD)) != NULL)
        if (!scrypt_set_membuf(&ctx->pass, &ctx->pass_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SALT)) != NULL)
        if (!scrypt_set_membuf(&ctx->salt, &ctx->salt_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SCRYPT_N))
        != NULL) {
        if (!OSSL_PARAM_get_uint64(p, &u64_value)
            || u64_value <= 1
            || !is_power_of_two(u64_value))
            return 0;
        ctx->N = u64_value;
    }

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SCRYPT_R))
        != NULL) {
        if (!OSSL_PARAM_get_uint64(p, &u64_value) || u64_value < 1)
            return 0;
        ctx->r = u64_value;
    }

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SCRYPT_P))
        != NULL) {
        if (!OSSL_PARAM_get_uint64(p, &u64_value) || u64_value < 1)
            return 0;
        ctx->p = u64_value;
    }

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SCRYPT_MAXMEM))
        != NULL) {
        if (!OSSL_PARAM_get_uint64(p, &u64_value) || u64_value < 1)
            return 0;
        ctx->maxmem_bytes = u64_value;
    }
    return 1;
}
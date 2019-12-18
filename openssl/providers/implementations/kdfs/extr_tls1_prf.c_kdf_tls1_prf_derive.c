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
struct TYPE_2__ {scalar_t__ seedlen; int /*<<< orphan*/  seed; int /*<<< orphan*/  seclen; int /*<<< orphan*/ * sec; int /*<<< orphan*/  P_sha1; int /*<<< orphan*/ * P_hash; } ;
typedef  TYPE_1__ TLS1_PRF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  PROV_R_MISSING_SECRET ; 
 int /*<<< orphan*/  PROV_R_MISSING_SEED ; 
 int tls1_prf_alg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned char*,size_t) ; 

__attribute__((used)) static int kdf_tls1_prf_derive(void *vctx, unsigned char *key,
                               size_t keylen)
{
    TLS1_PRF *ctx = (TLS1_PRF *)vctx;

    if (ctx->P_hash == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }
    if (ctx->sec == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_SECRET);
        return 0;
    }
    if (ctx->seedlen == 0) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_SEED);
        return 0;
    }

    return tls1_prf_alg(ctx->P_hash, ctx->P_sha1,
                        ctx->sec, ctx->seclen,
                        ctx->seed, ctx->seedlen,
                        key, keylen);
}
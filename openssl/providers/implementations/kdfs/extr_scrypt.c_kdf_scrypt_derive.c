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
struct TYPE_2__ {int /*<<< orphan*/  sha256; int /*<<< orphan*/  maxmem_bytes; int /*<<< orphan*/  p; int /*<<< orphan*/  r; int /*<<< orphan*/  N; int /*<<< orphan*/  salt_len; int /*<<< orphan*/ * salt; int /*<<< orphan*/  pass_len; int /*<<< orphan*/ * pass; } ;
typedef  TYPE_1__ KDF_SCRYPT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_MISSING_PASS ; 
 int /*<<< orphan*/  PROV_R_MISSING_SALT ; 
 int scrypt_alg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdf_scrypt_derive(void *vctx, unsigned char *key,
                             size_t keylen)
{
    KDF_SCRYPT *ctx = (KDF_SCRYPT *)vctx;

    if (ctx->pass == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_PASS);
        return 0;
    }

    if (ctx->salt == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_SALT);
        return 0;
    }

    return scrypt_alg((char *)ctx->pass, ctx->pass_len, ctx->salt,
                      ctx->salt_len, ctx->N, ctx->r, ctx->p,
                      ctx->maxmem_bytes, key, keylen, ctx->sha256);
}
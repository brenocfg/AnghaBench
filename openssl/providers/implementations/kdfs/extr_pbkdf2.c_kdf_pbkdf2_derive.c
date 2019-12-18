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
struct TYPE_2__ {int /*<<< orphan*/  lower_bound_checks; int /*<<< orphan*/  iter; int /*<<< orphan*/  salt_len; int /*<<< orphan*/ * salt; int /*<<< orphan*/  pass_len; int /*<<< orphan*/ * pass; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ KDF_PBKDF2 ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_MISSING_PASS ; 
 int /*<<< orphan*/  PROV_R_MISSING_SALT ; 
 int /*<<< orphan*/ * ossl_prov_digest_md (int /*<<< orphan*/ *) ; 
 int pbkdf2_derive (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdf_pbkdf2_derive(void *vctx, unsigned char *key,
                             size_t keylen)
{
    KDF_PBKDF2 *ctx = (KDF_PBKDF2 *)vctx;
    const EVP_MD *md = ossl_prov_digest_md(&ctx->digest);

    if (ctx->pass == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_PASS);
        return 0;
    }

    if (ctx->salt == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_SALT);
        return 0;
    }

    return pbkdf2_derive((char *)ctx->pass, ctx->pass_len,
                         ctx->salt, ctx->salt_len, ctx->iter,
                         md, key, keylen, ctx->lower_bound_checks);
}
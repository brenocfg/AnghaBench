#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pass_len; int /*<<< orphan*/  pass; int /*<<< orphan*/  salt; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ KDF_PBKDF2 ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_prov_digest_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kdf_pbkdf2_cleanup(KDF_PBKDF2 *ctx)
{
    ossl_prov_digest_reset(&ctx->digest);
    OPENSSL_free(ctx->salt);
    OPENSSL_clear_free(ctx->pass, ctx->pass_len);
    memset(ctx, 0, sizeof(*ctx));
}
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
struct TYPE_3__ {int /*<<< orphan*/  pass_len; int /*<<< orphan*/  pass; int /*<<< orphan*/  salt; } ;
typedef  TYPE_1__ KDF_SCRYPT ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdf_scrypt_init (TYPE_1__*) ; 

__attribute__((used)) static void kdf_scrypt_reset(void *vctx)
{
    KDF_SCRYPT *ctx = (KDF_SCRYPT *)vctx;

    OPENSSL_free(ctx->salt);
    OPENSSL_clear_free(ctx->pass, ctx->pass_len);
    kdf_scrypt_init(ctx);
}
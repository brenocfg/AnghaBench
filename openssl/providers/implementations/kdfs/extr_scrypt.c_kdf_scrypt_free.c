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
struct TYPE_4__ {int /*<<< orphan*/  sha256; } ;
typedef  TYPE_1__ KDF_SCRYPT ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_meth_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  kdf_scrypt_reset (TYPE_1__*) ; 

__attribute__((used)) static void kdf_scrypt_free(void *vctx)
{
    KDF_SCRYPT *ctx = (KDF_SCRYPT *)vctx;

    EVP_MD_meth_free(ctx->sha256);
    kdf_scrypt_reset(ctx);
    OPENSSL_free(ctx);
}
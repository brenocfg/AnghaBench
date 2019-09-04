#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cont; int start; int /*<<< orphan*/ * base64; } ;
typedef  TYPE_1__ BIO_B64_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * EVP_ENCODE_CTX_new () ; 
 int /*<<< orphan*/  EVP_F_B64_NEW ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static int b64_new(BIO *bi)
{
    BIO_B64_CTX *ctx;

    if ((ctx = OPENSSL_zalloc(sizeof(*ctx))) == NULL) {
        EVPerr(EVP_F_B64_NEW, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    ctx->cont = 1;
    ctx->start = 1;
    ctx->base64 = EVP_ENCODE_CTX_new();
    if (ctx->base64 == NULL) {
        OPENSSL_free(ctx);
        return 0;
    }

    BIO_set_data(bi, ctx);
    BIO_set_init(bi, 1);

    return 1;
}
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
struct TYPE_4__ {int /*<<< orphan*/  loader_ctx; } ;
typedef  TYPE_1__ OSSL_STORE_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int ossl_store_file_detach_pem_bio_int (int /*<<< orphan*/ ) ; 

int ossl_store_detach_pem_bio(OSSL_STORE_CTX *ctx)
{
    int loader_ret = ossl_store_file_detach_pem_bio_int(ctx->loader_ctx);

    OPENSSL_free(ctx);
    return loader_ret;
}
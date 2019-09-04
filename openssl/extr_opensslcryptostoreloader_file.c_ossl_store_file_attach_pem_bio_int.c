#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * file; } ;
struct TYPE_7__ {TYPE_1__ file; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; TYPE_2__ _; } ;
typedef  TYPE_3__ OSSL_STORE_LOADER_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_3__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_FILE_ATTACH_PEM_BIO_INT ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_pem ; 

OSSL_STORE_LOADER_CTX *ossl_store_file_attach_pem_bio_int(BIO *bp)
{
    OSSL_STORE_LOADER_CTX *ctx = OPENSSL_zalloc(sizeof(*ctx));

    if (ctx == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_FILE_ATTACH_PEM_BIO_INT,
                      ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    ctx->_.file.file = bp;
    ctx->type = is_pem;

    return ctx;
}
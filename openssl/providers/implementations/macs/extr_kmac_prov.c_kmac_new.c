#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kmac_data_st {void* provctx; int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 struct kmac_data_st* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  kmac_free (struct kmac_data_st*) ; 

__attribute__((used)) static struct kmac_data_st *kmac_new(void *provctx)
{
    struct kmac_data_st *kctx;

    if ((kctx = OPENSSL_zalloc(sizeof(*kctx))) == NULL
            || (kctx->ctx = EVP_MD_CTX_new()) == NULL) {
        kmac_free(kctx);
        return NULL;
    }
    kctx->provctx = provctx;
    return kctx;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  out_len; TYPE_1__ const* md; int /*<<< orphan*/ * ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  md_size; } ;
typedef  TYPE_1__ EVP_MD ;
typedef  TYPE_2__ EVP_MAC_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  kmac_free (TYPE_2__*) ; 

__attribute__((used)) static EVP_MAC_IMPL *kmac_new(const EVP_MD *md)
{
    EVP_MAC_IMPL *kctx = NULL;

    if ((kctx = OPENSSL_zalloc(sizeof(*kctx))) == NULL
            || (kctx->ctx = EVP_MD_CTX_new()) == NULL) {
        kmac_free(kctx);
        return NULL;
    }
    kctx->md = md;
    kctx->out_len = md->md_size;
    return kctx;
}
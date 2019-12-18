#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * (* dupctx ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/ * data; TYPE_4__* meth; } ;
typedef  TYPE_1__ EVP_MAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_MAC_CTX_DUP ; 
 int /*<<< orphan*/  EVP_MAC_CTX_free (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_MAC_up_ref (TYPE_4__*) ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 

EVP_MAC_CTX *EVP_MAC_CTX_dup(const EVP_MAC_CTX *src)
{
    EVP_MAC_CTX *dst;

    if (src->data == NULL)
        return NULL;

    dst = OPENSSL_malloc(sizeof(*dst));
    if (dst == NULL) {
        EVPerr(EVP_F_EVP_MAC_CTX_DUP, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    *dst = *src;
    if (!EVP_MAC_up_ref(dst->meth)) {
        EVPerr(EVP_F_EVP_MAC_CTX_DUP, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(dst);
        return NULL;
    }

    dst->data = src->meth->dupctx(src->data);
    if (dst->data == NULL) {
        EVP_MAC_CTX_free(dst);
        return NULL;
    }

    return dst;
}
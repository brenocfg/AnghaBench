#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * (* dupctx ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int /*<<< orphan*/ * data; TYPE_6__* meth; } ;
typedef  TYPE_1__ EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_KDF_CTX_DUP ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_KDF_up_ref (TYPE_6__*) ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 

EVP_KDF_CTX *EVP_KDF_CTX_dup(const EVP_KDF_CTX *src)
{
    EVP_KDF_CTX *dst;

    if (src == NULL || src->data == NULL || src->meth->dupctx == NULL)
        return NULL;

    dst = OPENSSL_malloc(sizeof(*dst));
    if (dst == NULL) {
        EVPerr(EVP_F_EVP_KDF_CTX_DUP, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    memcpy(dst, src, sizeof(*dst));
    if (!EVP_KDF_up_ref(dst->meth)) {
        EVPerr(EVP_F_EVP_KDF_CTX_DUP, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(dst);
        return NULL;
    }

    dst->data = src->meth->dupctx(src->data);
    if (dst->data == NULL) {
        EVP_KDF_CTX_free(dst);
        return NULL;
    }
    return dst;
}
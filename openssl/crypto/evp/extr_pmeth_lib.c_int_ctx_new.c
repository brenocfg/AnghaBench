#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int type; int /*<<< orphan*/ * engine; int /*<<< orphan*/ * pmeth_engine; } ;
struct TYPE_13__ {char const* algorithm; char const* propquery; TYPE_1__ const* pmeth; TYPE_3__* pkey; int /*<<< orphan*/  operation; int /*<<< orphan*/ * engine; int /*<<< orphan*/ * libctx; } ;
struct TYPE_12__ {scalar_t__ (* init ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_1__ EVP_PKEY_METHOD ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  TYPE_3__ EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 TYPE_1__* ENGINE_get_pkey_meth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ENGINE_get_pkey_meth_engine (int) ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_ENGINE_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_INT_CTX_NEW ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (TYPE_2__*) ; 
 int /*<<< orphan*/  EVP_PKEY_OP_UNDEFINED ; 
 TYPE_1__* EVP_PKEY_meth_find (int) ; 
 int /*<<< orphan*/  EVP_PKEY_up_ref (TYPE_3__*) ; 
 int /*<<< orphan*/  EVP_R_UNSUPPORTED_ALGORITHM ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* OBJ_nid2sn (int) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

__attribute__((used)) static EVP_PKEY_CTX *int_ctx_new(OPENSSL_CTX *libctx,
                                 EVP_PKEY *pkey, ENGINE *e,
                                 const char *name, const char *propquery,
                                 int id)
{
    EVP_PKEY_CTX *ret;
    const EVP_PKEY_METHOD *pmeth = NULL;

    /*
     * When using providers, the context is bound to the algo implementation
     * later.
     */
    if (pkey == NULL && e == NULL && id == -1)
        goto common;

    /* TODO(3.0) Legacy code should be removed when all is provider based */
    /* BEGIN legacy */
    if (id == -1) {
        if (pkey == NULL)
            return 0;
        id = pkey->type;
    }

    /*
     * Here, we extract what information we can for the purpose of
     * supporting usage with implementations from providers, to make
     * for a smooth transition from legacy stuff to provider based stuff.
     *
     * If an engine is given, this is entirely legacy, and we should not
     * pretend anything else, so we only set the name when no engine is
     * given.  If both are already given, someone made a mistake, and
     * since that can only happen internally, it's safe to make an
     * assertion.
     */
    if (!ossl_assert(e == NULL || name == NULL))
        return NULL;
    if (e == NULL)
        name = OBJ_nid2sn(id);
    propquery = NULL;
    /*
     * We were called using legacy data, or an EVP_PKEY, but an EVP_PKEY
     * isn't tied to a specific library context, so we fall back to the
     * default library context.
     * TODO(v3.0): an EVP_PKEY that doesn't originate from a leagacy key
     * structure only has the pkeys[] cache, where the first element is
     * considered the "origin".  Investigate if that could be a suitable
     * way to find a library context.
     */
    libctx = NULL;

#ifndef OPENSSL_NO_ENGINE
    if (e == NULL && pkey != NULL)
        e = pkey->pmeth_engine != NULL ? pkey->pmeth_engine : pkey->engine;
    /* Try to find an ENGINE which implements this method */
    if (e) {
        if (!ENGINE_init(e)) {
            EVPerr(EVP_F_INT_CTX_NEW, ERR_R_ENGINE_LIB);
            return NULL;
        }
    } else {
        e = ENGINE_get_pkey_meth_engine(id);
    }

    /*
     * If an ENGINE handled this method look it up. Otherwise use internal
     * tables.
     */
    if (e)
        pmeth = ENGINE_get_pkey_meth(e, id);
    else
#endif
        pmeth = EVP_PKEY_meth_find(id);

    if (pmeth == NULL) {
#ifndef OPENSSL_NO_ENGINE
        ENGINE_finish(e);
#endif
        EVPerr(EVP_F_INT_CTX_NEW, EVP_R_UNSUPPORTED_ALGORITHM);
        return NULL;
    }
    /* END legacy */

 common:
    ret = OPENSSL_zalloc(sizeof(*ret));
    if (ret == NULL) {
#ifndef OPENSSL_NO_ENGINE
        ENGINE_finish(e);
#endif
        EVPerr(EVP_F_INT_CTX_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->libctx = libctx;
    ret->algorithm = name;
    ret->propquery = propquery;
    ret->engine = e;
    ret->pmeth = pmeth;
    ret->operation = EVP_PKEY_OP_UNDEFINED;
    ret->pkey = pkey;
    if (pkey != NULL)
        EVP_PKEY_up_ref(pkey);

    if (pmeth != NULL && pmeth->init != NULL) {
        if (pmeth->init(ret) <= 0) {
            ret->pmeth = NULL;
            EVP_PKEY_CTX_free(ret);
            return NULL;
        }
    }

    return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_2__* meth; int /*<<< orphan*/ * engine; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  version; int /*<<< orphan*/  conv_form; int /*<<< orphan*/  enc_flag; TYPE_10__* group; int /*<<< orphan*/ * priv_key; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/  libctx; } ;
struct TYPE_21__ {scalar_t__ (* copy ) (TYPE_3__*,TYPE_3__ const*) ;int /*<<< orphan*/  (* finish ) (TYPE_3__*) ;} ;
struct TYPE_20__ {scalar_t__ (* keycopy ) (TYPE_3__*,TYPE_3__ const*) ;int /*<<< orphan*/  (* keyfinish ) (TYPE_3__*) ;} ;
struct TYPE_19__ {TYPE_1__* meth; } ;
typedef  int /*<<< orphan*/  EC_METHOD ;
typedef  TYPE_3__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_EC_KEY ; 
 int /*<<< orphan*/  CRYPTO_dup_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_KEY_COPY ; 
 int /*<<< orphan*/  EC_GROUP_copy (TYPE_10__*,TYPE_10__*) ; 
 int /*<<< orphan*/  EC_GROUP_free (TYPE_10__*) ; 
 int /*<<< orphan*/ * EC_GROUP_method_of (TYPE_10__*) ; 
 TYPE_10__* EC_GROUP_new_ex (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_10__*) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ENGINE_finish (int /*<<< orphan*/ *) ; 
 scalar_t__ ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 scalar_t__ stub3 (TYPE_3__*,TYPE_3__ const*) ; 
 scalar_t__ stub4 (TYPE_3__*,TYPE_3__ const*) ; 

EC_KEY *EC_KEY_copy(EC_KEY *dest, const EC_KEY *src)
{
    if (dest == NULL || src == NULL) {
        ECerr(EC_F_EC_KEY_COPY, ERR_R_PASSED_NULL_PARAMETER);
        return NULL;
    }
    if (src->meth != dest->meth) {
        if (dest->meth->finish != NULL)
            dest->meth->finish(dest);
        if (dest->group && dest->group->meth->keyfinish)
            dest->group->meth->keyfinish(dest);
#if !defined(OPENSSL_NO_ENGINE) && !defined(FIPS_MODE)
        if (ENGINE_finish(dest->engine) == 0)
            return 0;
        dest->engine = NULL;
#endif
    }
    dest->libctx = src->libctx;
    /* copy the parameters */
    if (src->group != NULL) {
        const EC_METHOD *meth = EC_GROUP_method_of(src->group);
        /* clear the old group */
        EC_GROUP_free(dest->group);
        dest->group = EC_GROUP_new_ex(src->libctx, meth);
        if (dest->group == NULL)
            return NULL;
        if (!EC_GROUP_copy(dest->group, src->group))
            return NULL;

        /*  copy the public key */
        if (src->pub_key != NULL) {
            EC_POINT_free(dest->pub_key);
            dest->pub_key = EC_POINT_new(src->group);
            if (dest->pub_key == NULL)
                return NULL;
            if (!EC_POINT_copy(dest->pub_key, src->pub_key))
                return NULL;
        }
        /* copy the private key */
        if (src->priv_key != NULL) {
            if (dest->priv_key == NULL) {
                dest->priv_key = BN_new();
                if (dest->priv_key == NULL)
                    return NULL;
            }
            if (!BN_copy(dest->priv_key, src->priv_key))
                return NULL;
            if (src->group->meth->keycopy
                && src->group->meth->keycopy(dest, src) == 0)
                return NULL;
        }
    }


    /* copy the rest */
    dest->enc_flag = src->enc_flag;
    dest->conv_form = src->conv_form;
    dest->version = src->version;
    dest->flags = src->flags;
#ifndef FIPS_MODE
    if (!CRYPTO_dup_ex_data(CRYPTO_EX_INDEX_EC_KEY,
                            &dest->ex_data, &src->ex_data))
        return NULL;
#endif

    if (src->meth != dest->meth) {
#if !defined(OPENSSL_NO_ENGINE) && !defined(FIPS_MODE)
        if (src->engine != NULL && ENGINE_init(src->engine) == 0)
            return NULL;
        dest->engine = src->engine;
#endif
        dest->meth = src->meth;
    }

    if (src->meth->copy != NULL && src->meth->copy(dest, src) == 0)
        return NULL;

    return dest;
}
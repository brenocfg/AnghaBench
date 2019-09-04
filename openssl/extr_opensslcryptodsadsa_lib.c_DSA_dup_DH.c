#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * priv_key; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/ * q; int /*<<< orphan*/ * g; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ DSA ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DH_new () ; 
 int /*<<< orphan*/  DH_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DH *DSA_dup_DH(const DSA *r)
{
    /*
     * DSA has p, q, g, optional pub_key, optional priv_key. DH has p,
     * optional length, g, optional pub_key, optional priv_key, optional q.
     */

    DH *ret = NULL;
    BIGNUM *p = NULL, *q = NULL, *g = NULL, *pub_key = NULL, *priv_key = NULL;

    if (r == NULL)
        goto err;
    ret = DH_new();
    if (ret == NULL)
        goto err;
    if (r->p != NULL || r->g != NULL || r->q != NULL) {
        if (r->p == NULL || r->g == NULL || r->q == NULL) {
            /* Shouldn't happen */
            goto err;
        }
        p = BN_dup(r->p);
        g = BN_dup(r->g);
        q = BN_dup(r->q);
        if (p == NULL || g == NULL || q == NULL || !DH_set0_pqg(ret, p, q, g))
            goto err;
        p = g = q = NULL;
    }

    if (r->pub_key != NULL) {
        pub_key = BN_dup(r->pub_key);
        if (pub_key == NULL)
            goto err;
        if (r->priv_key != NULL) {
            priv_key = BN_dup(r->priv_key);
            if (priv_key == NULL)
                goto err;
        }
        if (!DH_set0_key(ret, pub_key, priv_key))
            goto err;
    } else if (r->priv_key != NULL) {
        /* Shouldn't happen */
        goto err;
    }

    return ret;

 err:
    BN_free(p);
    BN_free(g);
    BN_free(q);
    BN_free(pub_key);
    BN_free(priv_key);
    DH_free(ret);
    return NULL;
}
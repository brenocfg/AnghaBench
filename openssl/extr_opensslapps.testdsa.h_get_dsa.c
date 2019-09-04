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
struct TYPE_3__ {int /*<<< orphan*/  g_l; int /*<<< orphan*/  g; int /*<<< orphan*/  q_l; int /*<<< orphan*/  q; int /*<<< orphan*/  p_l; int /*<<< orphan*/  p; int /*<<< orphan*/  pub_l; int /*<<< orphan*/  pub; int /*<<< orphan*/  priv_l; int /*<<< orphan*/  priv; } ;
typedef  TYPE_1__ testdsa ;
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_new () ; 
 int /*<<< orphan*/  DSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dsa_ptr (TYPE_1__,int) ; 

DSA *get_dsa(int dsa_bits)
{
    DSA *dsa;
    BIGNUM *priv_key, *pub_key, *p, *q, *g;
    testdsa dsa_t;

    switch (dsa_bits) {
    case 512:
        set_dsa_ptr(dsa_t, 512);
        break;
    case 1024:
        set_dsa_ptr(dsa_t, 1024);
        break;
    case 2048:
        set_dsa_ptr(dsa_t, 2048);
        break;
    default:
        return NULL;
    }

    if ((dsa = DSA_new()) == NULL)
        return NULL;
    priv_key = BN_bin2bn(dsa_t.priv, dsa_t.priv_l, NULL);
    pub_key = BN_bin2bn(dsa_t.pub, dsa_t.pub_l, NULL);
    p = BN_bin2bn(dsa_t.p, dsa_t.p_l, NULL);
    q = BN_bin2bn(dsa_t.q, dsa_t.q_l, NULL);
    g = BN_bin2bn(dsa_t.g, dsa_t.g_l, NULL);
    if ((priv_key == NULL) || (pub_key == NULL) || (p == NULL) || (q == NULL)
         || (g == NULL)) {
        goto err;
    }
    if (!DSA_set0_pqg(dsa, p, q, g))
        goto err;

    if (!DSA_set0_key(dsa, pub_key, priv_key))
        goto err;

    return dsa;
 err:
    DSA_free(dsa);
    BN_free(priv_key);
    BN_free(pub_key);
    BN_free(p);
    BN_free(q);
    BN_free(g);
    return NULL;
}
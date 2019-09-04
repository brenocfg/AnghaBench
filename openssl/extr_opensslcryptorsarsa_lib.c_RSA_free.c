#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* bignum_data; int /*<<< orphan*/  mt_blinding; int /*<<< orphan*/  blinding; int /*<<< orphan*/  prime_infos; int /*<<< orphan*/  pss; int /*<<< orphan*/  iqmp; int /*<<< orphan*/  dmq1; int /*<<< orphan*/  dmp1; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  d; int /*<<< orphan*/  e; int /*<<< orphan*/  n; int /*<<< orphan*/  lock; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  engine; TYPE_1__* meth; int /*<<< orphan*/  references; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* finish ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ RSA ;

/* Variables and functions */
 int /*<<< orphan*/  BN_BLINDING_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_RSA ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  RSA_PSS_PARAMS_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsa_multip_info_free ; 
 int /*<<< orphan*/  sk_RSA_PRIME_INFO_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void RSA_free(RSA *r)
{
    int i;

    if (r == NULL)
        return;

    CRYPTO_DOWN_REF(&r->references, &i, r->lock);
    REF_PRINT_COUNT("RSA", r);
    if (i > 0)
        return;
    REF_ASSERT_ISNT(i < 0);

    if (r->meth != NULL && r->meth->finish != NULL)
        r->meth->finish(r);
#ifndef OPENSSL_NO_ENGINE
    ENGINE_finish(r->engine);
#endif

    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_RSA, r, &r->ex_data);

    CRYPTO_THREAD_lock_free(r->lock);

    BN_free(r->n);
    BN_free(r->e);
    BN_clear_free(r->d);
    BN_clear_free(r->p);
    BN_clear_free(r->q);
    BN_clear_free(r->dmp1);
    BN_clear_free(r->dmq1);
    BN_clear_free(r->iqmp);
    RSA_PSS_PARAMS_free(r->pss);
    sk_RSA_PRIME_INFO_pop_free(r->prime_infos, rsa_multip_info_free);
    BN_BLINDING_free(r->blinding);
    BN_BLINDING_free(r->mt_blinding);
    OPENSSL_free(r->bignum_data);
    OPENSSL_free(r);
}
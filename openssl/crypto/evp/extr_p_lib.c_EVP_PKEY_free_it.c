#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pmeth_engine; int /*<<< orphan*/ * engine; TYPE_2__ pkey; TYPE_1__* ameth; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* pkey_free ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evp_keymgmt_clear_pkey_cache (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void EVP_PKEY_free_it(EVP_PKEY *x)
{
    /* internal function; x is never NULL */

    evp_keymgmt_clear_pkey_cache(x);

    if (x->ameth && x->ameth->pkey_free) {
        x->ameth->pkey_free(x);
        x->pkey.ptr = NULL;
    }
#ifndef OPENSSL_NO_ENGINE
    ENGINE_finish(x->engine);
    x->engine = NULL;
    ENGINE_finish(x->pmeth_engine);
    x->pmeth_engine = NULL;
#endif
}
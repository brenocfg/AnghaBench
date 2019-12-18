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
struct TYPE_8__ {TYPE_1__ const* meth; int /*<<< orphan*/ * engine; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* init ) (TYPE_2__*) ;int /*<<< orphan*/  (* finish ) (TYPE_2__*) ;} ;
typedef  TYPE_1__ const DSA_METHOD ;
typedef  TYPE_2__ DSA ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

int DSA_set_method(DSA *dsa, const DSA_METHOD *meth)
{
    /*
     * NB: The caller is specifically setting a method, so it's not up to us
     * to deal with which ENGINE it comes from.
     */
    const DSA_METHOD *mtmp;
    mtmp = dsa->meth;
    if (mtmp->finish)
        mtmp->finish(dsa);
#ifndef OPENSSL_NO_ENGINE
    ENGINE_finish(dsa->engine);
    dsa->engine = NULL;
#endif
    dsa->meth = meth;
    if (meth->init)
        meth->init(dsa);
    return 1;
}
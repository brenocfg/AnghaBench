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
struct TYPE_8__ {void (* finish ) (TYPE_1__*) ;int (* init ) (TYPE_1__*) ;} ;
struct TYPE_7__ {TYPE_2__ const* meth; int /*<<< orphan*/ * engine; } ;
typedef  TYPE_2__ EC_KEY_METHOD ;
typedef  TYPE_1__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*) ; 

int EC_KEY_set_method(EC_KEY *key, const EC_KEY_METHOD *meth)
{
    void (*finish)(EC_KEY *key) = key->meth->finish;

    if (finish != NULL)
        finish(key);

#if !defined(OPENSSL_NO_ENGINE) && !defined(FIPS_MODE)
    ENGINE_finish(key->engine);
    key->engine = NULL;
#endif

    key->meth = meth;
    if (meth->init != NULL)
        return meth->init(key);
    return 1;
}
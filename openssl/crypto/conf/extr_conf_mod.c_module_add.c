#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  conf_init_func ;
typedef  int /*<<< orphan*/  conf_finish_func ;
struct TYPE_7__ {struct TYPE_7__* name; int /*<<< orphan*/ * finish; int /*<<< orphan*/ * init; int /*<<< orphan*/ * dso; } ;
typedef  int /*<<< orphan*/  DSO ;
typedef  TYPE_1__ CONF_MODULE ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_F_MODULE_ADD ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_strdup (char const*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/ * sk_CONF_MODULE_new_null () ; 
 int /*<<< orphan*/  sk_CONF_MODULE_push (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * supported_modules ; 

__attribute__((used)) static CONF_MODULE *module_add(DSO *dso, const char *name,
                               conf_init_func *ifunc, conf_finish_func *ffunc)
{
    CONF_MODULE *tmod = NULL;
    if (supported_modules == NULL)
        supported_modules = sk_CONF_MODULE_new_null();
    if (supported_modules == NULL)
        return NULL;
    if ((tmod = OPENSSL_zalloc(sizeof(*tmod))) == NULL) {
        CONFerr(CONF_F_MODULE_ADD, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    tmod->dso = dso;
    tmod->name = OPENSSL_strdup(name);
    tmod->init = ifunc;
    tmod->finish = ffunc;
    if (tmod->name == NULL) {
        OPENSSL_free(tmod);
        return NULL;
    }

    if (!sk_CONF_MODULE_push(supported_modules, tmod)) {
        OPENSSL_free(tmod->name);
        OPENSSL_free(tmod);
        return NULL;
    }

    return tmod;
}
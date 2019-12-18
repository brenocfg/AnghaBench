#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parameters; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_2__ INFOPAIR ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_VERSION_STR ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_utf8_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* OSSL_PROV_PARAM_MODULE_FILENAME ; 
 int /*<<< orphan*/  ossl_provider_module_path (TYPE_1__ const*) ; 
 int sk_INFOPAIR_num (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_INFOPAIR_value (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int core_get_params(const OSSL_PROVIDER *prov, OSSL_PARAM params[])
{
    int i;
    OSSL_PARAM *p;

    if ((p = OSSL_PARAM_locate(params, "openssl-version")) != NULL)
        OSSL_PARAM_set_utf8_ptr(p, OPENSSL_VERSION_STR);
    if ((p = OSSL_PARAM_locate(params, "provider-name")) != NULL)
        OSSL_PARAM_set_utf8_ptr(p, prov->name);

#ifndef FIPS_MODE
    if ((p = OSSL_PARAM_locate(params, OSSL_PROV_PARAM_MODULE_FILENAME)) != NULL)
        OSSL_PARAM_set_utf8_ptr(p, ossl_provider_module_path(prov));
#endif

    if (prov->parameters == NULL)
        return 1;

    for (i = 0; i < sk_INFOPAIR_num(prov->parameters); i++) {
        INFOPAIR *pair = sk_INFOPAIR_value(prov->parameters, i);

        if ((p = OSSL_PARAM_locate(params, pair->name)) != NULL)
            OSSL_PARAM_set_utf8_ptr(p, pair->value);
    }
    return 1;
}
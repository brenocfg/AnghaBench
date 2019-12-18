#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data_type; char* data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/ * ENGINE_by_id (char*) ; 
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 char* OSSL_ALG_PARAM_PROPERTIES ; 
 scalar_t__ OSSL_PARAM_UTF8_STRING ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,char*) ; 

__attribute__((used)) static int load_common(const OSSL_PARAM params[], const char **propquery,
                       ENGINE **engine)
{
    const OSSL_PARAM *p;

    *propquery = NULL;
    p = OSSL_PARAM_locate_const(params, OSSL_ALG_PARAM_PROPERTIES);
    if (p != NULL) {
        if (p->data_type != OSSL_PARAM_UTF8_STRING)
            return 0;
        *propquery = p->data;
    }

    *engine = NULL;
    /* TODO legacy stuff, to be removed */
    /* Inside the FIPS module, we don't support legacy ciphers */
#if !defined(FIPS_MODE) && !defined(OPENSSL_NO_ENGINE)
    p = OSSL_PARAM_locate_const(params, "engine");
    if (p != NULL) {
        if (p->data_type != OSSL_PARAM_UTF8_STRING)
            return 0;
        ENGINE_finish(*engine);
        *engine = ENGINE_by_id(p->data);
        if (*engine == NULL)
            return 0;
    }
#endif
    return 1;
}
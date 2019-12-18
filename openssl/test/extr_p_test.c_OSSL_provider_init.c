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
struct TYPE_7__ {int function_id; } ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  TYPE_1__ OSSL_DISPATCH ;

/* Variables and functions */
#define  OSSL_FUNC_CORE_GETTABLE_PARAMS 129 
#define  OSSL_FUNC_CORE_GET_PARAMS 128 
 int /*<<< orphan*/  OSSL_get_core_get_params (TYPE_1__ const*) ; 
 int /*<<< orphan*/  OSSL_get_core_gettable_params (TYPE_1__ const*) ; 
 int /*<<< orphan*/  c_get_params ; 
 int /*<<< orphan*/  c_gettable_params ; 
 TYPE_1__* p_test_table ; 

int OSSL_provider_init(const OSSL_PROVIDER *provider,
                       const OSSL_DISPATCH *in,
                       const OSSL_DISPATCH **out,
                       void **provctx)
{
    for (; in->function_id != 0; in++) {
        switch (in->function_id) {
        case OSSL_FUNC_CORE_GETTABLE_PARAMS:
            c_gettable_params = OSSL_get_core_gettable_params(in);
            break;
        case OSSL_FUNC_CORE_GET_PARAMS:
            c_get_params = OSSL_get_core_get_params(in);
            break;
        default:
            /* Just ignore anything we don't understand */
            break;
        }
    }

    /* Because we use this in get_params, we need to pass it back */
    *provctx = (void *)provider;

    *out = p_test_table;
    return 1;
}
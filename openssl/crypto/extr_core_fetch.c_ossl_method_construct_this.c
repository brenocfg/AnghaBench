#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct construct_data_st {int /*<<< orphan*/  mcm_data; TYPE_1__* mcm; int /*<<< orphan*/  operation_id; int /*<<< orphan*/ * store; int /*<<< orphan*/  libctx; scalar_t__ force_store; } ;
struct TYPE_5__ {int /*<<< orphan*/  property_definition; int /*<<< orphan*/  algorithm_names; int /*<<< orphan*/  implementation; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* destruct ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* put ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;void* (* construct ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  TYPE_2__ OSSL_ALGORITHM ;

/* Variables and functions */
 void* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ossl_method_construct_this(OSSL_PROVIDER *provider,
                                       const OSSL_ALGORITHM *algo,
                                       int no_store, void *cbdata)
{
    struct construct_data_st *data = cbdata;
    void *method = NULL;

    if ((method = data->mcm->construct(algo->algorithm_names,
                                       algo->implementation, provider,
                                       data->mcm_data)) == NULL)
        return;

    /*
     * Note regarding putting the method in stores:
     *
     * we don't need to care if it actually got in or not here.
     * If it didn't get in, it will simply not be available when
     * ossl_method_construct() tries to get it from the store.
     *
     * It is *expected* that the put function increments the refcnt
     * of the passed method.
     */

    if (data->force_store || !no_store) {
        /*
         * If we haven't been told not to store,
         * add to the global store
         */
        data->mcm->put(data->libctx, NULL, method, provider,
                       data->operation_id, algo->algorithm_names,
                       algo->property_definition, data->mcm_data);
    }

    data->mcm->put(data->libctx, data->store, method, provider,
                   data->operation_id, algo->algorithm_names,
                   algo->property_definition, data->mcm_data);

    /* refcnt-- because we're dropping the reference */
    data->mcm->destruct(method, data->mcm_data);
}
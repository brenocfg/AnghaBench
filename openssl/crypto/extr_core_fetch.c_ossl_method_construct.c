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
struct construct_data_st {int operation_id; int force_store; int /*<<< orphan*/ * store; void* mcm_data; TYPE_1__* mcm; int /*<<< orphan*/ * libctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dealloc_tmp_store ) (int /*<<< orphan*/ *) ;void* (* get ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/ * (* alloc_tmp_store ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ OSSL_METHOD_CONSTRUCT_METHOD ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_algorithm_do_all (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct construct_data_st*) ; 
 int /*<<< orphan*/  ossl_method_construct_this ; 
 void* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *) ; 
 void* stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 

void *ossl_method_construct(OPENSSL_CTX *libctx, int operation_id,
                            int force_store,
                            OSSL_METHOD_CONSTRUCT_METHOD *mcm, void *mcm_data)
{
    void *method = NULL;

    if ((method = mcm->get(libctx, NULL, mcm_data)) == NULL) {
        struct construct_data_st cbdata;

        /*
         * We have a temporary store to be able to easily search among new
         * items, or items that should find themselves in the global store.
         */
        if ((cbdata.store = mcm->alloc_tmp_store(libctx)) == NULL)
            goto fin;

        cbdata.libctx = libctx;
        cbdata.operation_id = operation_id;
        cbdata.force_store = force_store;
        cbdata.mcm = mcm;
        cbdata.mcm_data = mcm_data;
        ossl_algorithm_do_all(libctx, operation_id, NULL,
                              ossl_method_construct_this, &cbdata);

        method = mcm->get(libctx, cbdata.store, mcm_data);
        mcm->dealloc_tmp_store(cbdata.store);
    }

 fin:
    return method;
}
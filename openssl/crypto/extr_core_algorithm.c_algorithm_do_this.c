#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct algorithm_data_st {int operation_id; int /*<<< orphan*/  data; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ *,TYPE_1__ const*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * algorithm_names; } ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  TYPE_1__ OSSL_ALGORITHM ;

/* Variables and functions */
 int OSSL_OP__HIGHEST ; 
 TYPE_1__* ossl_provider_query_operation (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__ const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int algorithm_do_this(OSSL_PROVIDER *provider, void *cbdata)
{
    struct algorithm_data_st *data = cbdata;
    int no_store = 0;    /* Assume caching is ok */
    int first_operation = 1;
    int last_operation = OSSL_OP__HIGHEST;
    int cur_operation;
    int ok = 0;

    if (data->operation_id != 0)
        first_operation = last_operation = data->operation_id;

    for (cur_operation = first_operation;
         cur_operation <= last_operation;
         cur_operation++) {
        const OSSL_ALGORITHM *map =
            ossl_provider_query_operation(provider, data->operation_id,
                                          &no_store);

        if (map == NULL)
            break;

        ok = 1;                  /* As long as we've found *something* */
        while (map->algorithm_names != NULL) {
            const OSSL_ALGORITHM *thismap = map++;

            data->fn(provider, thismap, no_store, data->data);
        }
    }

    return ok;
}
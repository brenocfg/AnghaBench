#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct method_data_st {int /*<<< orphan*/  (* refcnt_up_method ) (void*) ;int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 void* get_default_method_store (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_method_store_fetch (void*,int /*<<< orphan*/ ,char const*,void**) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void *get_method_from_store(OPENSSL_CTX *libctx, void *store,
                                   const char *propquery, void *data)
{
    struct method_data_st *methdata = data;
    void *method = NULL;

    if (store == NULL
        && (store = get_default_method_store(libctx)) == NULL)
        return NULL;

    (void)ossl_method_store_fetch(store, methdata->nid, propquery, &method);

    if (method != NULL
        && !methdata->refcnt_up_method(method)) {
        method = NULL;
    }
    return method;
}
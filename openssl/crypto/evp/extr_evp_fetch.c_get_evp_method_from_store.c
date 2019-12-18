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
typedef  int /*<<< orphan*/  uint32_t ;
struct evp_method_data_st {int name_id; char* names; int /*<<< orphan*/  (* refcnt_up_method ) (void*) ;int /*<<< orphan*/  propquery; int /*<<< orphan*/  operation_id; } ;
typedef  int /*<<< orphan*/  OSSL_NAMEMAP ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_SEPARATOR ; 
 int /*<<< orphan*/  evp_method_id (int /*<<< orphan*/ ,int) ; 
 void* get_evp_method_store (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_method_store_fetch (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int ossl_namemap_name2num_n (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/ * ossl_namemap_stored (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void *get_evp_method_from_store(OPENSSL_CTX *libctx, void *store,
                                       void *data)
{
    struct evp_method_data_st *methdata = data;
    void *method = NULL;
    int name_id;
    uint32_t meth_id;

    /*
     * get_evp_method_from_store() is only called to try and get the method
     * that evp_generic_fetch() is asking for, and the operation id as well
     * as the name or name id are passed via methdata.
     */
    if ((name_id = methdata->name_id) == 0) {
        OSSL_NAMEMAP *namemap = ossl_namemap_stored(libctx);
        const char *names = methdata->names;
        const char *q = strchr(names, NAME_SEPARATOR);
        size_t l = (q == NULL ? strlen(names) : (size_t)(q - names));

        if (namemap == 0)
            return NULL;
        name_id = ossl_namemap_name2num_n(namemap, names, l);
    }

    if (name_id == 0
        || (meth_id = evp_method_id(methdata->operation_id, name_id)) == 0)
        return NULL;

    if (store == NULL
        && (store = get_evp_method_store(libctx)) == NULL)
        return NULL;

    (void)ossl_method_store_fetch(store, meth_id, methdata->propquery,
                                  &method);

    if (method != NULL
        && !methdata->refcnt_up_method(method)) {
        method = NULL;
    }
    return method;
}
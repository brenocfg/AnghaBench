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
struct method_data_st {int (* nid_method ) (void*) ;int /*<<< orphan*/  destruct_method; scalar_t__ (* refcnt_up_method ) (void*) ;} ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int NID_undef ; 
 void* get_default_method_store (int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_method_store_add (void*,int,char const*,void*,int /*<<< orphan*/ ) ; 
 int stub1 (void*) ; 
 scalar_t__ stub2 (void*) ; 

__attribute__((used)) static int put_method_in_store(OPENSSL_CTX *libctx, void *store,
                               const char *propdef,
                               void *method, void *data)
{
    struct method_data_st *methdata = data;
    int nid = methdata->nid_method(method);

    if (nid == NID_undef)
        return 0;

    if (store == NULL
        && (store = get_default_method_store(libctx)) == NULL)
        return 0;

    if (methdata->refcnt_up_method(method)
        && ossl_method_store_add(store, nid, propdef, method,
                                 methdata->destruct_method))
        return 1;
    return 0;
}
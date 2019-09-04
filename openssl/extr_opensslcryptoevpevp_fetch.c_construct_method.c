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
struct method_data_st {void* (* method_from_dispatch ) (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; scalar_t__ length; int /*<<< orphan*/  flags; int /*<<< orphan*/  ln; int /*<<< orphan*/  sn; int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_DISPATCH ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_FLAG_DYNAMIC ; 
 int NID_undef ; 
 int OBJ_add_object (TYPE_1__*) ; 
 int /*<<< orphan*/  OBJ_new_nid (int) ; 
 int OBJ_sn2nid (char const*) ; 
 void* stub1 (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *construct_method(const char *algorithm_name,
                              const OSSL_DISPATCH *fns, OSSL_PROVIDER *prov,
                              void *data)
{
    struct method_data_st *methdata = data;
    void *method = NULL;
    int nid = OBJ_sn2nid(algorithm_name);

    if (nid == NID_undef) {
        /* Create a new NID for that name on the fly */
        ASN1_OBJECT tmpobj;

        /* This is the same as OBJ_create() but without requiring a OID */
        tmpobj.nid = OBJ_new_nid(1);
        tmpobj.sn = tmpobj.ln = methdata->name;
        tmpobj.flags = ASN1_OBJECT_FLAG_DYNAMIC;
        tmpobj.length = 0;
        tmpobj.data = NULL;

        nid = OBJ_add_object(&tmpobj);
    }

    if (nid == NID_undef)
        return NULL;

    method = methdata->method_from_dispatch(nid, fns, prov);
    if (method == NULL)
        return NULL;
    return method;
}
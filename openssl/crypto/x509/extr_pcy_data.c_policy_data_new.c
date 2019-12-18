#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * qualifier_set; int /*<<< orphan*/ * valid_policy; int /*<<< orphan*/  flags; int /*<<< orphan*/ * expected_policy_set; } ;
typedef  TYPE_1__ X509_POLICY_DATA ;
struct TYPE_8__ {int /*<<< orphan*/ * qualifiers; int /*<<< orphan*/ * policyid; } ;
typedef  TYPE_2__ POLICYINFO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OBJ_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  POLICY_DATA_FLAG_CRITICAL ; 
 int /*<<< orphan*/  X509V3_F_POLICY_DATA_NEW ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_ASN1_OBJECT_new_null () ; 

X509_POLICY_DATA *policy_data_new(POLICYINFO *policy,
                                  const ASN1_OBJECT *cid, int crit)
{
    X509_POLICY_DATA *ret;
    ASN1_OBJECT *id;

    if (policy == NULL && cid == NULL)
        return NULL;
    if (cid) {
        id = OBJ_dup(cid);
        if (id == NULL)
            return NULL;
    } else
        id = NULL;
    ret = OPENSSL_zalloc(sizeof(*ret));
    if (ret == NULL) {
        X509V3err(X509V3_F_POLICY_DATA_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->expected_policy_set = sk_ASN1_OBJECT_new_null();
    if (ret->expected_policy_set == NULL) {
        OPENSSL_free(ret);
        ASN1_OBJECT_free(id);
        X509V3err(X509V3_F_POLICY_DATA_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if (crit)
        ret->flags = POLICY_DATA_FLAG_CRITICAL;

    if (id)
        ret->valid_policy = id;
    else {
        ret->valid_policy = policy->policyid;
        policy->policyid = NULL;
    }

    if (policy) {
        ret->qualifier_set = policy->qualifiers;
        policy->qualifiers = NULL;
    }

    return ret;
}
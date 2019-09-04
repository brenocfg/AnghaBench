#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  expected_policy_set; int /*<<< orphan*/  flags; int /*<<< orphan*/  qualifier_set; } ;
typedef  TYPE_2__ X509_POLICY_DATA ;
struct TYPE_15__ {int /*<<< orphan*/  data; TYPE_1__* anyPolicy; } ;
typedef  TYPE_3__ X509_POLICY_CACHE ;
struct TYPE_16__ {int /*<<< orphan*/  ex_flags; TYPE_3__* policy_cache; } ;
typedef  TYPE_4__ X509 ;
struct TYPE_17__ {int /*<<< orphan*/ * subjectDomainPolicy; int /*<<< orphan*/ * issuerDomainPolicy; } ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  qualifier_set; } ;
typedef  int /*<<< orphan*/  POLICY_MAPPINGS ;
typedef  TYPE_5__ POLICY_MAPPING ;

/* Variables and functions */
 int /*<<< orphan*/  EXFLAG_INVALID_POLICY ; 
 scalar_t__ NID_any_policy ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int POLICY_DATA_FLAG_CRITICAL ; 
 int /*<<< orphan*/  POLICY_DATA_FLAG_MAPPED ; 
 int /*<<< orphan*/  POLICY_DATA_FLAG_MAPPED_ANY ; 
 int /*<<< orphan*/  POLICY_DATA_FLAG_SHARED_QUALIFIERS ; 
 int /*<<< orphan*/  POLICY_MAPPING_free ; 
 TYPE_2__* policy_cache_find_data (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  policy_data_free (TYPE_2__*) ; 
 TYPE_2__* policy_data_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sk_POLICY_MAPPING_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_POLICY_MAPPING_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* sk_POLICY_MAPPING_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_X509_POLICY_DATA_push (int /*<<< orphan*/ ,TYPE_2__*) ; 

int policy_cache_set_mapping(X509 *x, POLICY_MAPPINGS *maps)
{
    POLICY_MAPPING *map;
    X509_POLICY_DATA *data;
    X509_POLICY_CACHE *cache = x->policy_cache;
    int i;
    int ret = 0;
    if (sk_POLICY_MAPPING_num(maps) == 0) {
        ret = -1;
        goto bad_mapping;
    }
    for (i = 0; i < sk_POLICY_MAPPING_num(maps); i++) {
        map = sk_POLICY_MAPPING_value(maps, i);
        /* Reject if map to or from anyPolicy */
        if ((OBJ_obj2nid(map->subjectDomainPolicy) == NID_any_policy)
            || (OBJ_obj2nid(map->issuerDomainPolicy) == NID_any_policy)) {
            ret = -1;
            goto bad_mapping;
        }

        /* Attempt to find matching policy data */
        data = policy_cache_find_data(cache, map->issuerDomainPolicy);
        /* If we don't have anyPolicy can't map */
        if (data == NULL && !cache->anyPolicy)
            continue;

        /* Create a NODE from anyPolicy */
        if (data == NULL) {
            data = policy_data_new(NULL, map->issuerDomainPolicy,
                                   cache->anyPolicy->flags
                                   & POLICY_DATA_FLAG_CRITICAL);
            if (data == NULL)
                goto bad_mapping;
            data->qualifier_set = cache->anyPolicy->qualifier_set;
            /*
             * map->issuerDomainPolicy = NULL;
             */
            data->flags |= POLICY_DATA_FLAG_MAPPED_ANY;
            data->flags |= POLICY_DATA_FLAG_SHARED_QUALIFIERS;
            if (!sk_X509_POLICY_DATA_push(cache->data, data)) {
                policy_data_free(data);
                goto bad_mapping;
            }
        } else
            data->flags |= POLICY_DATA_FLAG_MAPPED;
        if (!sk_ASN1_OBJECT_push(data->expected_policy_set,
                                 map->subjectDomainPolicy))
            goto bad_mapping;
        map->subjectDomainPolicy = NULL;

    }

    ret = 1;
 bad_mapping:
    if (ret == -1)
        x->ex_flags |= EXFLAG_INVALID_POLICY;
    sk_POLICY_MAPPING_pop_free(maps, POLICY_MAPPING_free);
    return ret;

}
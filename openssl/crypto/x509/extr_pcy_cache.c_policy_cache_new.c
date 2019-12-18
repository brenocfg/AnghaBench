#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int any_skip; int explicit_skip; int map_skip; int /*<<< orphan*/ * data; int /*<<< orphan*/ * anyPolicy; } ;
typedef  TYPE_1__ X509_POLICY_CACHE ;
struct TYPE_11__ {int /*<<< orphan*/  ex_flags; TYPE_1__* policy_cache; } ;
typedef  TYPE_2__ X509 ;
struct TYPE_12__ {int /*<<< orphan*/ * inhibitPolicyMapping; int /*<<< orphan*/ * requireExplicitPolicy; } ;
typedef  int /*<<< orphan*/  POLICY_MAPPINGS ;
typedef  TYPE_3__ POLICY_CONSTRAINTS ;
typedef  int /*<<< orphan*/  CERTIFICATEPOLICIES ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EXFLAG_INVALID_POLICY ; 
 int /*<<< orphan*/  NID_certificate_policies ; 
 int /*<<< orphan*/  NID_inhibit_any_policy ; 
 int /*<<< orphan*/  NID_policy_constraints ; 
 int /*<<< orphan*/  NID_policy_mappings ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  POLICY_CONSTRAINTS_free (TYPE_3__*) ; 
 int /*<<< orphan*/  X509V3_F_POLICY_CACHE_NEW ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* X509_get_ext_d2i (TYPE_2__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int policy_cache_create (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  policy_cache_set_int (int*,int /*<<< orphan*/ *) ; 
 int policy_cache_set_mapping (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int policy_cache_new(X509 *x)
{
    X509_POLICY_CACHE *cache;
    ASN1_INTEGER *ext_any = NULL;
    POLICY_CONSTRAINTS *ext_pcons = NULL;
    CERTIFICATEPOLICIES *ext_cpols = NULL;
    POLICY_MAPPINGS *ext_pmaps = NULL;
    int i;

    if (x->policy_cache != NULL)
        return 1;
    cache = OPENSSL_malloc(sizeof(*cache));
    if (cache == NULL) {
        X509V3err(X509V3_F_POLICY_CACHE_NEW, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    cache->anyPolicy = NULL;
    cache->data = NULL;
    cache->any_skip = -1;
    cache->explicit_skip = -1;
    cache->map_skip = -1;

    x->policy_cache = cache;

    /*
     * Handle requireExplicitPolicy *first*. Need to process this even if we
     * don't have any policies.
     */
    ext_pcons = X509_get_ext_d2i(x, NID_policy_constraints, &i, NULL);

    if (!ext_pcons) {
        if (i != -1)
            goto bad_cache;
    } else {
        if (!ext_pcons->requireExplicitPolicy
            && !ext_pcons->inhibitPolicyMapping)
            goto bad_cache;
        if (!policy_cache_set_int(&cache->explicit_skip,
                                  ext_pcons->requireExplicitPolicy))
            goto bad_cache;
        if (!policy_cache_set_int(&cache->map_skip,
                                  ext_pcons->inhibitPolicyMapping))
            goto bad_cache;
    }

    /* Process CertificatePolicies */

    ext_cpols = X509_get_ext_d2i(x, NID_certificate_policies, &i, NULL);
    /*
     * If no CertificatePolicies extension or problem decoding then there is
     * no point continuing because the valid policies will be NULL.
     */
    if (!ext_cpols) {
        /* If not absent some problem with extension */
        if (i != -1)
            goto bad_cache;
        return 1;
    }

    i = policy_cache_create(x, ext_cpols, i);

    /* NB: ext_cpols freed by policy_cache_set_policies */

    if (i <= 0)
        return i;

    ext_pmaps = X509_get_ext_d2i(x, NID_policy_mappings, &i, NULL);

    if (!ext_pmaps) {
        /* If not absent some problem with extension */
        if (i != -1)
            goto bad_cache;
    } else {
        i = policy_cache_set_mapping(x, ext_pmaps);
        if (i <= 0)
            goto bad_cache;
    }

    ext_any = X509_get_ext_d2i(x, NID_inhibit_any_policy, &i, NULL);

    if (!ext_any) {
        if (i != -1)
            goto bad_cache;
    } else if (!policy_cache_set_int(&cache->any_skip, ext_any))
        goto bad_cache;
    goto just_cleanup;

 bad_cache:
    x->ex_flags |= EXFLAG_INVALID_POLICY;

 just_cleanup:
    POLICY_CONSTRAINTS_free(ext_pcons);
    ASN1_INTEGER_free(ext_any);
    return 1;

}
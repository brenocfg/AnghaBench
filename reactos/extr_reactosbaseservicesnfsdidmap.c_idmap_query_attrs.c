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
struct idmap_lookup {int dummy; } ;
struct idmap_config {int /*<<< orphan*/ * attributes; int /*<<< orphan*/  base; } ;
struct idmap_context {int /*<<< orphan*/  ldap; struct idmap_config config; } ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  LDAPMessage ;

/* Variables and functions */
 scalar_t__ ATTR_ISSET (unsigned int const,int) ; 
 int FILTER_LEN ; 
 int LDAP_NO_RESULTS_RETURNED ; 
 int LDAP_NO_SUCH_ATTRIBUTE ; 
 int /*<<< orphan*/  LDAP_SCOPE_SUBTREE ; 
 int LdapMapErrorToWin32 (int) ; 
 int /*<<< orphan*/  eprintf (char*,char*,int,int,...) ; 
 int idmap_filter (struct idmap_config*,struct idmap_lookup const*,char*,int) ; 
 int /*<<< orphan*/  ldap_err2stringA (int) ; 
 int /*<<< orphan*/ * ldap_first_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldap_get_values (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 int ldap_search_st (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int idmap_query_attrs(
    struct idmap_context *context,
    const struct idmap_lookup *lookup,
    const unsigned attributes,
    const unsigned optional,
    PCHAR *values[],
    const int len)
{
    char filter[FILTER_LEN];
    struct idmap_config *config = &context->config;
    LDAPMessage *res = NULL, *entry;
    int i, status;

    /* format the ldap filter */
    status = idmap_filter(config, lookup, filter, FILTER_LEN);
    if (status)
        goto out;

    /* send the ldap query */
    status = ldap_search_st(context->ldap, config->base,
        LDAP_SCOPE_SUBTREE, filter, NULL, 0, NULL, &res);
    if (status) {
        eprintf("ldap search for '%s' failed with %d: %s\n",
            filter, status, ldap_err2stringA(status));
        status = LdapMapErrorToWin32(status);
        goto out;
    }

    entry = ldap_first_entry(context->ldap, res);
    if (entry == NULL) {
        status = LDAP_NO_RESULTS_RETURNED;
        eprintf("ldap search for '%s' failed with %d: %s\n",
            filter, status, ldap_err2stringA(status));
        status = LdapMapErrorToWin32(status);
        goto out;
    }

    /* fetch the attributes */
    for (i = 0; i < len; i++) {
        if (ATTR_ISSET(attributes, i)) {
            values[i] = ldap_get_values(context->ldap,
                entry, config->attributes[i]);

            /* fail if required attributes are missing */
            if (values[i] == NULL && !ATTR_ISSET(optional, i)) {
                status = LDAP_NO_SUCH_ATTRIBUTE;
                eprintf("ldap entry for '%s' missing required "
                    "attribute '%s', returning %d: %s\n",
                    filter, config->attributes[i],
                    status, ldap_err2stringA(status));
                status = LdapMapErrorToWin32(status);
                goto out;
            }
        }
    }
out:
    if (res) ldap_msgfree(res);
    return status;
}
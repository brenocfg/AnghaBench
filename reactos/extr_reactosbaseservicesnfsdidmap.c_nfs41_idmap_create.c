#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int version; int timeout; int /*<<< orphan*/  hostname; int /*<<< orphan*/  port; } ;
struct idmap_context {TYPE_1__ config; int /*<<< orphan*/ * ldap; int /*<<< orphan*/  groups; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int GetLastError () ; 
 int /*<<< orphan*/  LDAP_OPT_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  LDAP_OPT_TIMELIMIT ; 
 int LDAP_SUCCESS ; 
 int LdapGetLastError () ; 
 int LdapMapErrorToWin32 (int) ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  cache_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct idmap_context* calloc (int,int) ; 
 int config_init (TYPE_1__*) ; 
 int /*<<< orphan*/  eprintf (char*,int,...) ; 
 int /*<<< orphan*/  group_cache_ops ; 
 int /*<<< orphan*/  ldap_err2stringA (int) ; 
 int /*<<< orphan*/ * ldap_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ldap_set_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nfs41_idmap_free (struct idmap_context*) ; 
 int /*<<< orphan*/  user_cache_ops ; 

int nfs41_idmap_create(
    struct idmap_context **context_out)
{
    struct idmap_context *context;
    int status = NO_ERROR;

    context = calloc(1, sizeof(struct idmap_context));
    if (context == NULL) {
        status = GetLastError();
        goto out;
    }

    /* initialize the caches */
    cache_init(&context->users, &user_cache_ops);
    cache_init(&context->groups, &group_cache_ops);

    /* load ldap configuration from file */
    status = config_init(&context->config);
    if (status) {
        eprintf("config_init() failed with %d\n", status);
        goto out_err_free;
    }

    /* initialize ldap and configure options */
    context->ldap = ldap_init(context->config.hostname, context->config.port);
    if (context->ldap == NULL) {
        status = LdapGetLastError();
        eprintf("ldap_init(%s) failed with %d: %s\n",
            context->config.hostname, status, ldap_err2stringA(status));
        status = LdapMapErrorToWin32(status);
        goto out_err_free;
    }

    status = ldap_set_option(context->ldap, LDAP_OPT_PROTOCOL_VERSION,
        (void *)&context->config.version);
    if (status != LDAP_SUCCESS) {
        eprintf("ldap_set_option(version=%d) failed with %d\n",
            context->config.version, status);
        status = LdapMapErrorToWin32(status);
        goto out_err_free;
    }

    if (context->config.timeout) {
        status = ldap_set_option(context->ldap, LDAP_OPT_TIMELIMIT,
            (void *)&context->config.timeout);
        if (status != LDAP_SUCCESS) {
            eprintf("ldap_set_option(timeout=%d) failed with %d\n",
                context->config.timeout, status);
            status = LdapMapErrorToWin32(status);
            goto out_err_free;
        }
    }

    *context_out = context;
out:
    return status;

out_err_free:
    nfs41_idmap_free(context);
    goto out;
}
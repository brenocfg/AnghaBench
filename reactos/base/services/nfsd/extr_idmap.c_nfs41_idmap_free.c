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
struct idmap_context {int /*<<< orphan*/  groups; int /*<<< orphan*/  users; scalar_t__ ldap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct idmap_context*) ; 
 int /*<<< orphan*/  ldap_unbind (scalar_t__) ; 

void nfs41_idmap_free(
    struct idmap_context *context)
{
    /* clean up the connection */
    if (context->ldap)
        ldap_unbind(context->ldap);

    cache_cleanup(&context->users);
    cache_cleanup(&context->groups);
    free(context);
}
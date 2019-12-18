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
typedef  int /*<<< orphan*/  u32 ;
struct gss_ctx {int /*<<< orphan*/  mech_type; } ;
struct auth_domain {int dummy; } ;

/* Variables and functions */
 struct auth_domain* auth_domain_find (char*) ; 
 char* gss_service_to_auth_domain_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct auth_domain *
find_gss_auth_domain(struct gss_ctx *ctx, u32 svc)
{
	char *name;

	name = gss_service_to_auth_domain_name(ctx->mech_type, svc);
	if (!name)
		return NULL;
	return auth_domain_find(name);
}
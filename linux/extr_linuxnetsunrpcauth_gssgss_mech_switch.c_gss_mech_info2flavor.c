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
struct rpcsec_gss_info {int /*<<< orphan*/  service; int /*<<< orphan*/  qop; int /*<<< orphan*/  oid; } ;
struct gss_api_mech {int dummy; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_AUTH_MAXFLAVOR ; 
 struct gss_api_mech* gss_mech_get_by_OID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_mech_put (struct gss_api_mech*) ; 
 int /*<<< orphan*/  gss_svc_to_pseudoflavor (struct gss_api_mech*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rpc_authflavor_t gss_mech_info2flavor(struct rpcsec_gss_info *info)
{
	rpc_authflavor_t pseudoflavor;
	struct gss_api_mech *gm;

	gm = gss_mech_get_by_OID(&info->oid);
	if (gm == NULL)
		return RPC_AUTH_MAXFLAVOR;

	pseudoflavor = gss_svc_to_pseudoflavor(gm, info->qop, info->service);

	gss_mech_put(gm);
	return pseudoflavor;
}
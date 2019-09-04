#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rpcsec_gss_info {int /*<<< orphan*/  service; int /*<<< orphan*/  qop; TYPE_1__ oid; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct gss_api_mech {int gm_pf_num; TYPE_3__* gm_pfs; TYPE_2__ gm_oid; } ;
typedef  scalar_t__ rpc_authflavor_t ;
struct TYPE_6__ {scalar_t__ pseudoflavor; int /*<<< orphan*/  service; int /*<<< orphan*/  qop; } ;

/* Variables and functions */
 int ENOENT ; 
 struct gss_api_mech* gss_mech_get_by_pseudoflavor (scalar_t__) ; 
 int /*<<< orphan*/  gss_mech_put (struct gss_api_mech*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gss_mech_flavor2info(rpc_authflavor_t pseudoflavor,
			 struct rpcsec_gss_info *info)
{
	struct gss_api_mech *gm;
	int i;

	gm = gss_mech_get_by_pseudoflavor(pseudoflavor);
	if (gm == NULL)
		return -ENOENT;

	for (i = 0; i < gm->gm_pf_num; i++) {
		if (gm->gm_pfs[i].pseudoflavor == pseudoflavor) {
			memcpy(info->oid.data, gm->gm_oid.data, gm->gm_oid.len);
			info->oid.len = gm->gm_oid.len;
			info->qop = gm->gm_pfs[i].qop;
			info->service = gm->gm_pfs[i].service;
			gss_mech_put(gm);
			return 0;
		}
	}

	gss_mech_put(gm);
	return -ENOENT;
}
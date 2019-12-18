#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct q6core_svc_api_info {scalar_t__ api_branch_version; int /*<<< orphan*/  api_version; } ;
struct avcs_svc_info {int service_id; int /*<<< orphan*/  version; } ;
struct avcs_svc_api_info {int service_id; scalar_t__ api_branch_version; int /*<<< orphan*/  api_version; } ;
struct TYPE_8__ {int is_version_requested; int /*<<< orphan*/  lock; TYPE_2__* svc_version; scalar_t__ get_version_supported; TYPE_1__* fwk_version; scalar_t__ fwk_version_supported; } ;
struct TYPE_7__ {int num_services; struct avcs_svc_info* svc_api_info; } ;
struct TYPE_6__ {int num_services; struct avcs_svc_api_info* svc_api_info; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 TYPE_3__* g_core ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int q6core_get_fwk_versions (TYPE_3__*) ; 
 int /*<<< orphan*/  q6core_get_svc_versions (TYPE_3__*) ; 

int q6core_get_svc_api_info(int svc_id, struct q6core_svc_api_info *ainfo)
{
	int i;
	int ret = -ENOTSUPP;

	if (!g_core || !ainfo)
		return 0;

	mutex_lock(&g_core->lock);
	if (!g_core->is_version_requested) {
		if (q6core_get_fwk_versions(g_core) == -ENOTSUPP)
			q6core_get_svc_versions(g_core);
		g_core->is_version_requested = true;
	}

	if (g_core->fwk_version_supported) {
		for (i = 0; i < g_core->fwk_version->num_services; i++) {
			struct avcs_svc_api_info *info;

			info = &g_core->fwk_version->svc_api_info[i];
			if (svc_id != info->service_id)
				continue;

			ainfo->api_version = info->api_version;
			ainfo->api_branch_version = info->api_branch_version;
			ret = 0;
			break;
		}
	} else if (g_core->get_version_supported) {
		for (i = 0; i < g_core->svc_version->num_services; i++) {
			struct avcs_svc_info *info;

			info = &g_core->svc_version->svc_api_info[i];
			if (svc_id != info->service_id)
				continue;

			ainfo->api_version = info->version;
			ainfo->api_branch_version = 0;
			ret = 0;
			break;
		}
	}

	mutex_unlock(&g_core->lock);

	return ret;
}
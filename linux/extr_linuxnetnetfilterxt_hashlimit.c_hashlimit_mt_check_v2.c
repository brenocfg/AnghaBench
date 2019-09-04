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
struct xt_mtchk_param {struct xt_hashlimit_mtinfo2* matchinfo; } ;
struct xt_hashlimit_mtinfo2 {int /*<<< orphan*/  name; int /*<<< orphan*/  hinfo; int /*<<< orphan*/  cfg; } ;
struct hashlimit_cfg3 {int dummy; } ;

/* Variables and functions */
 int cfg_copy (struct hashlimit_cfg3*,void*,int) ; 
 int hashlimit_mt_check_common (struct xt_mtchk_param const*,int /*<<< orphan*/ *,struct hashlimit_cfg3*,int /*<<< orphan*/ ,int) ; 
 int xt_check_proc_name (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hashlimit_mt_check_v2(const struct xt_mtchk_param *par)
{
	struct xt_hashlimit_mtinfo2 *info = par->matchinfo;
	struct hashlimit_cfg3 cfg = {};
	int ret;

	ret = xt_check_proc_name(info->name, sizeof(info->name));
	if (ret)
		return ret;

	ret = cfg_copy(&cfg, (void *)&info->cfg, 2);
	if (ret)
		return ret;

	return hashlimit_mt_check_common(par, &info->hinfo,
					 &cfg, info->name, 2);
}
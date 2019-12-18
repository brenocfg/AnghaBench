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
struct xt_mtchk_param {struct xt_hashlimit_mtinfo3* matchinfo; } ;
struct xt_hashlimit_mtinfo3 {int /*<<< orphan*/  name; int /*<<< orphan*/  cfg; int /*<<< orphan*/  hinfo; } ;

/* Variables and functions */
 int hashlimit_mt_check_common (struct xt_mtchk_param const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int xt_check_proc_name (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hashlimit_mt_check(const struct xt_mtchk_param *par)
{
	struct xt_hashlimit_mtinfo3 *info = par->matchinfo;
	int ret;

	ret = xt_check_proc_name(info->name, sizeof(info->name));
	if (ret)
		return ret;

	return hashlimit_mt_check_common(par, &info->hinfo, &info->cfg,
					 info->name, 3);
}
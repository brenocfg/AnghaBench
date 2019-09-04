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
struct TYPE_2__ {int /*<<< orphan*/  all; } ;
struct xt_recent_mtinfo_v1 {TYPE_1__ mask; } ;
struct xt_recent_mtinfo_v0 {int dummy; } ;
struct xt_recent_mtinfo {int dummy; } ;
struct xt_mtchk_param {struct xt_recent_mtinfo_v0* matchinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct xt_recent_mtinfo_v1*,struct xt_recent_mtinfo_v0 const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int recent_mt_check (struct xt_mtchk_param const*,struct xt_recent_mtinfo_v1*) ; 

__attribute__((used)) static int recent_mt_check_v0(const struct xt_mtchk_param *par)
{
	const struct xt_recent_mtinfo_v0 *info_v0 = par->matchinfo;
	struct xt_recent_mtinfo_v1 info_v1;

	/* Copy revision 0 structure to revision 1 */
	memcpy(&info_v1, info_v0, sizeof(struct xt_recent_mtinfo));
	/* Set default mask to ensure backward compatible behaviour */
	memset(info_v1.mask.all, 0xFF, sizeof(info_v1.mask.all));

	return recent_mt_check(par, &info_v1);
}
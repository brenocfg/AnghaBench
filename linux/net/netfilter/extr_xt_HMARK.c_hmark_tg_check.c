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
struct xt_tgchk_param {struct xt_hmark_info* targinfo; } ;
struct xt_hmark_info {int flags; scalar_t__ proto_mask; int /*<<< orphan*/  hmodulus; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  XT_HMARK_DPORT ; 
 int /*<<< orphan*/  XT_HMARK_DPORT_MASK ; 
 int XT_HMARK_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XT_HMARK_METHOD_L3 ; 
 int /*<<< orphan*/  XT_HMARK_SPI ; 
 int /*<<< orphan*/  XT_HMARK_SPI_MASK ; 
 int /*<<< orphan*/  XT_HMARK_SPORT ; 
 int /*<<< orphan*/  XT_HMARK_SPORT_MASK ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,char const*) ; 

__attribute__((used)) static int hmark_tg_check(const struct xt_tgchk_param *par)
{
	const struct xt_hmark_info *info = par->targinfo;
	const char *errmsg = "proto mask must be zero with L3 mode";

	if (!info->hmodulus)
		return -EINVAL;

	if (info->proto_mask &&
	    (info->flags & XT_HMARK_FLAG(XT_HMARK_METHOD_L3)))
		goto err;

	if (info->flags & XT_HMARK_FLAG(XT_HMARK_SPI_MASK) &&
	    (info->flags & (XT_HMARK_FLAG(XT_HMARK_SPORT_MASK) |
			     XT_HMARK_FLAG(XT_HMARK_DPORT_MASK))))
		return -EINVAL;

	if (info->flags & XT_HMARK_FLAG(XT_HMARK_SPI) &&
	    (info->flags & (XT_HMARK_FLAG(XT_HMARK_SPORT) |
			     XT_HMARK_FLAG(XT_HMARK_DPORT)))) {
		errmsg = "spi-set and port-set can't be combined";
		goto err;
	}
	return 0;
err:
	pr_info_ratelimited("%s\n", errmsg);
	return -EINVAL;
}
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
struct xt_mtchk_param {struct ip6t_ipv6header_info* matchinfo; } ;
struct ip6t_ipv6header_info {int invflags; int /*<<< orphan*/  modeflag; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ipv6header_mt6_check(const struct xt_mtchk_param *par)
{
	const struct ip6t_ipv6header_info *info = par->matchinfo;

	/* invflags is 0 or 0xff in hard mode */
	if ((!info->modeflag) && info->invflags != 0x00 &&
	    info->invflags != 0xFF)
		return -EINVAL;

	return 0;
}
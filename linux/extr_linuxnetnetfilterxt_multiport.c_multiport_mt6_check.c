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
struct xt_multiport_v1 {int /*<<< orphan*/  count; int /*<<< orphan*/  flags; } ;
struct xt_mtchk_param {struct xt_multiport_v1* matchinfo; struct ip6t_ip6* entryinfo; } ;
struct ip6t_ip6 {int /*<<< orphan*/  invflags; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int multiport_mt6_check(const struct xt_mtchk_param *par)
{
	const struct ip6t_ip6 *ip = par->entryinfo;
	const struct xt_multiport_v1 *multiinfo = par->matchinfo;

	return check(ip->proto, ip->invflags, multiinfo->flags,
		     multiinfo->count) ? 0 : -EINVAL;
}
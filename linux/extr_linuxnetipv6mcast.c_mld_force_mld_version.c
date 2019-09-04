#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int force_mld_version; } ;
struct inet6_dev {TYPE_3__ cnf; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__* devconf_all; } ;
struct TYPE_8__ {TYPE_2__ ipv6; } ;
struct TYPE_5__ {scalar_t__ force_mld_version; } ;

/* Variables and functions */
 TYPE_4__* dev_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mld_force_mld_version(const struct inet6_dev *idev)
{
	/* Normally, both are 0 here. If enforcement to a particular is
	 * being used, individual device enforcement will have a lower
	 * precedence over 'all' device (.../conf/all/force_mld_version).
	 */

	if (dev_net(idev->dev)->ipv6.devconf_all->force_mld_version != 0)
		return dev_net(idev->dev)->ipv6.devconf_all->force_mld_version;
	else
		return idev->cnf.force_mld_version;
}
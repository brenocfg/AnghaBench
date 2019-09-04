#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xt_tgchk_param {TYPE_2__* net; } ;
struct TYPE_3__ {int notrack_deprecated_warning; } ;
struct TYPE_4__ {TYPE_1__ xt; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int notrack_chk(const struct xt_tgchk_param *par)
{
	if (!par->net->xt.notrack_deprecated_warning) {
		pr_info("netfilter: NOTRACK target is deprecated, "
			"use CT instead or upgrade iptables\n");
		par->net->xt.notrack_deprecated_warning = true;
	}
	return 0;
}
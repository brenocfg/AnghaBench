#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* devconf_dflt; } ;
struct net {TYPE_5__ ipv6; } ;
struct TYPE_6__ {int /*<<< orphan*/  initialized; } ;
struct TYPE_7__ {TYPE_1__ stable_secret; } ;
struct inet6_dev {TYPE_2__ cnf; } ;
struct TYPE_8__ {int /*<<< orphan*/  initialized; } ;
struct TYPE_9__ {TYPE_3__ stable_secret; } ;

/* Variables and functions */
 int EINVAL ; 
 int IN6_ADDR_GEN_MODE_STABLE_PRIVACY ; 

__attribute__((used)) static int check_stable_privacy(struct inet6_dev *idev, struct net *net,
				int mode)
{
	if (mode == IN6_ADDR_GEN_MODE_STABLE_PRIVACY &&
	    !idev->cnf.stable_secret.initialized &&
	    !net->ipv6.devconf_dflt->stable_secret.initialized)
		return -EINVAL;
	return 1;
}
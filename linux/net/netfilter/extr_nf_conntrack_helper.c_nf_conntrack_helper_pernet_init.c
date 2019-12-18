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
struct TYPE_2__ {int auto_assign_helper_warned; int /*<<< orphan*/  sysctl_auto_assign_helper; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_auto_assign_helper ; 

void nf_conntrack_helper_pernet_init(struct net *net)
{
	net->ct.auto_assign_helper_warned = false;
	net->ct.sysctl_auto_assign_helper = nf_ct_auto_assign_helper;
}
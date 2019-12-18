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
struct TYPE_2__ {int /*<<< orphan*/  ecache_dwork; int /*<<< orphan*/  sysctl_events; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecache_work ; 
 int /*<<< orphan*/  nf_ct_events ; 

void nf_conntrack_ecache_pernet_init(struct net *net)
{
	net->ct.sysctl_events = nf_ct_events;
	INIT_DELAYED_WORK(&net->ct.ecache_dwork, ecache_work);
}
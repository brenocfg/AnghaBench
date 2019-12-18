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
struct TYPE_2__ {scalar_t__ expect_count; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int exp_proc_init (struct net*) ; 

int nf_conntrack_expect_pernet_init(struct net *net)
{
	net->ct.expect_count = 0;
	return exp_proc_init(net);
}
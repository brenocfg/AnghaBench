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
struct TYPE_2__ {int /*<<< orphan*/  fqdir; } ;
struct net {TYPE_1__ nf_frag; } ;

/* Variables and functions */
 int /*<<< orphan*/  fqdir_pre_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_ct_net_pre_exit(struct net *net)
{
	fqdir_pre_exit(net->nf_frag.fqdir);
}
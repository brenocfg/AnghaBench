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
struct nf_icmp_net {int dummy; } ;
struct TYPE_3__ {struct nf_icmp_net icmp; } ;
struct TYPE_4__ {TYPE_1__ nf_ct_proto; } ;
struct net {TYPE_2__ ct; } ;

/* Variables and functions */

__attribute__((used)) static inline struct nf_icmp_net *icmp_pernet(struct net *net)
{
	return &net->ct.nf_ct_proto.icmp;
}
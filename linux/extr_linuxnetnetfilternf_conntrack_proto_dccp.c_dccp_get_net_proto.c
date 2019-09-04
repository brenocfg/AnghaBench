#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nf_proto_net {int dummy; } ;
struct TYPE_4__ {struct nf_proto_net pn; } ;
struct TYPE_5__ {TYPE_1__ dccp; } ;
struct TYPE_6__ {TYPE_2__ nf_ct_proto; } ;
struct net {TYPE_3__ ct; } ;

/* Variables and functions */

__attribute__((used)) static struct nf_proto_net *dccp_get_net_proto(struct net *net)
{
	return &net->ct.nf_ct_proto.dccp.pn;
}
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
struct seg6_local_lwt {TYPE_2__* srh; TYPE_1__* desc; } ;
struct nlattr {int dummy; } ;
struct lwtunnel_state {int dummy; } ;
struct TYPE_4__ {int hdrlen; } ;
struct TYPE_3__ {unsigned long attrs; } ;

/* Variables and functions */
 int MAX_PROG_NAME ; 
 int SEG6_LOCAL_BPF ; 
 int SEG6_LOCAL_IIF ; 
 int SEG6_LOCAL_NH4 ; 
 int SEG6_LOCAL_NH6 ; 
 int SEG6_LOCAL_OIF ; 
 int SEG6_LOCAL_SRH ; 
 int SEG6_LOCAL_TABLE ; 
 int nla_total_size (int) ; 
 struct seg6_local_lwt* seg6_local_lwtunnel (struct lwtunnel_state*) ; 

__attribute__((used)) static int seg6_local_get_encap_size(struct lwtunnel_state *lwt)
{
	struct seg6_local_lwt *slwt = seg6_local_lwtunnel(lwt);
	unsigned long attrs;
	int nlsize;

	nlsize = nla_total_size(4); /* action */

	attrs = slwt->desc->attrs;

	if (attrs & (1 << SEG6_LOCAL_SRH))
		nlsize += nla_total_size((slwt->srh->hdrlen + 1) << 3);

	if (attrs & (1 << SEG6_LOCAL_TABLE))
		nlsize += nla_total_size(4);

	if (attrs & (1 << SEG6_LOCAL_NH4))
		nlsize += nla_total_size(4);

	if (attrs & (1 << SEG6_LOCAL_NH6))
		nlsize += nla_total_size(16);

	if (attrs & (1 << SEG6_LOCAL_IIF))
		nlsize += nla_total_size(4);

	if (attrs & (1 << SEG6_LOCAL_OIF))
		nlsize += nla_total_size(4);

	if (attrs & (1 << SEG6_LOCAL_BPF))
		nlsize += nla_total_size(sizeof(struct nlattr)) +
		       nla_total_size(MAX_PROG_NAME) +
		       nla_total_size(4);

	return nlsize;
}
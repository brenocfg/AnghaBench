#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mpls_shim_hdr {int dummy; } ;
struct mpls_iptunnel_encap {int labels; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int mpls_encap_size(struct mpls_iptunnel_encap *en)
{
	/* The size of the layer 2.5 labels to be added for this route */
	return en->labels * sizeof(struct mpls_shim_hdr);
}
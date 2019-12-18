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
struct sk_buff {int encapsulation; scalar_t__ data; } ;
struct TYPE_3__ {int (* gro_complete ) (struct sk_buff*,int) ;} ;
struct packet_offload {TYPE_1__ callbacks; } ;
struct gre_base_hdr {int flags; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  gso_type; } ;

/* Variables and functions */
 int ENOENT ; 
 int GRE_CSUM ; 
 scalar_t__ GRE_HEADER_SECTION ; 
 int GRE_KEY ; 
 int /*<<< orphan*/  SKB_GSO_GRE ; 
 struct packet_offload* gro_find_complete_by_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_set_inner_mac_header (struct sk_buff*,int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int stub1 (struct sk_buff*,int) ; 

__attribute__((used)) static int gre_gro_complete(struct sk_buff *skb, int nhoff)
{
	struct gre_base_hdr *greh = (struct gre_base_hdr *)(skb->data + nhoff);
	struct packet_offload *ptype;
	unsigned int grehlen = sizeof(*greh);
	int err = -ENOENT;
	__be16 type;

	skb->encapsulation = 1;
	skb_shinfo(skb)->gso_type = SKB_GSO_GRE;

	type = greh->protocol;
	if (greh->flags & GRE_KEY)
		grehlen += GRE_HEADER_SECTION;

	if (greh->flags & GRE_CSUM)
		grehlen += GRE_HEADER_SECTION;

	rcu_read_lock();
	ptype = gro_find_complete_by_type(type);
	if (ptype)
		err = ptype->callbacks.gro_complete(skb, nhoff + grehlen);

	rcu_read_unlock();

	skb_set_inner_mac_header(skb, nhoff + grehlen);

	return err;
}
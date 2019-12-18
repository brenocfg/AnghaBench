#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct pptp_gre_header {int flags; scalar_t__ protocol; int /*<<< orphan*/  call_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  key; } ;
struct TYPE_11__ {TYPE_4__ gre; scalar_t__ all; } ;
struct TYPE_12__ {TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
struct TYPE_8__ {TYPE_1__ gre; scalar_t__ all; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ src; TYPE_3__ dst; } ;
struct net {int dummy; } ;
struct gre_base_hdr {int flags; scalar_t__ protocol; int /*<<< orphan*/  call_id; } ;
typedef  int /*<<< orphan*/  _grehdr ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ GRE_PROTO_PPP ; 
 int GRE_VERSION ; 
 int GRE_VERSION_1 ; 
 int /*<<< orphan*/  gre_keymap_lookup (struct net*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 struct pptp_gre_header* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct pptp_gre_header*) ; 

bool gre_pkt_to_tuple(const struct sk_buff *skb, unsigned int dataoff,
		      struct net *net, struct nf_conntrack_tuple *tuple)
{
	const struct pptp_gre_header *pgrehdr;
	struct pptp_gre_header _pgrehdr;
	__be16 srckey;
	const struct gre_base_hdr *grehdr;
	struct gre_base_hdr _grehdr;

	/* first only delinearize old RFC1701 GRE header */
	grehdr = skb_header_pointer(skb, dataoff, sizeof(_grehdr), &_grehdr);
	if (!grehdr || (grehdr->flags & GRE_VERSION) != GRE_VERSION_1) {
		/* try to behave like "nf_conntrack_proto_generic" */
		tuple->src.u.all = 0;
		tuple->dst.u.all = 0;
		return true;
	}

	/* PPTP header is variable length, only need up to the call_id field */
	pgrehdr = skb_header_pointer(skb, dataoff, 8, &_pgrehdr);
	if (!pgrehdr)
		return true;

	if (grehdr->protocol != GRE_PROTO_PPP) {
		pr_debug("Unsupported GRE proto(0x%x)\n", ntohs(grehdr->protocol));
		return false;
	}

	tuple->dst.u.gre.key = pgrehdr->call_id;
	srckey = gre_keymap_lookup(net, tuple);
	tuple->src.u.gre.key = srckey;

	return true;
}
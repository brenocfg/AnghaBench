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
struct xt_hmark_info {int dummy; } ;
struct sk_buff {int dummy; } ;
struct hmark_tuple {int /*<<< orphan*/  uports; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  hmark_swap_ports (int /*<<< orphan*/ *,struct xt_hmark_info const*) ; 
 int proto_ports_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_bits (struct sk_buff const*,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
hmark_set_tuple_ports(const struct sk_buff *skb, unsigned int nhoff,
		      struct hmark_tuple *t, const struct xt_hmark_info *info)
{
	int protoff;

	protoff = proto_ports_offset(t->proto);
	if (protoff < 0)
		return;

	nhoff += protoff;
	if (skb_copy_bits(skb, nhoff, &t->uports, sizeof(t->uports)) < 0)
		return;

	hmark_swap_ports(&t->uports, info);
}
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
struct xsk_queue {int /*<<< orphan*/  nentries; } ;
struct xdp_diag_ring {int /*<<< orphan*/  entries; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  dr ;

/* Variables and functions */
 int nla_put (struct sk_buff*,int,int,struct xdp_diag_ring*) ; 

__attribute__((used)) static int xsk_diag_put_ring(const struct xsk_queue *queue, int nl_type,
			     struct sk_buff *nlskb)
{
	struct xdp_diag_ring dr = {};

	dr.entries = queue->nentries;
	return nla_put(nlskb, nl_type, sizeof(dr), &dr);
}
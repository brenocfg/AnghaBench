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
struct TYPE_2__ {int /*<<< orphan*/  ip; } ;
struct nf_nat_range2 {int /*<<< orphan*/  max_proto; int /*<<< orphan*/  min_proto; TYPE_1__ max_addr; TYPE_1__ min_addr; int /*<<< orphan*/  flags; TYPE_1__ base_proto; } ;
struct nf_nat_ipv4_range {int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  max_ip; int /*<<< orphan*/  min_ip; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xt_nat_convert_range(struct nf_nat_range2 *dst,
				 const struct nf_nat_ipv4_range *src)
{
	memset(&dst->min_addr, 0, sizeof(dst->min_addr));
	memset(&dst->max_addr, 0, sizeof(dst->max_addr));
	memset(&dst->base_proto, 0, sizeof(dst->base_proto));

	dst->flags	 = src->flags;
	dst->min_addr.ip = src->min_ip;
	dst->max_addr.ip = src->max_ip;
	dst->min_proto	 = src->min;
	dst->max_proto	 = src->max;
}
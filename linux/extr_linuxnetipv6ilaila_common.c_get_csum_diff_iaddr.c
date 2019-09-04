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
struct TYPE_2__ {scalar_t__ v64; } ;
struct ila_params {int /*<<< orphan*/  locator; int /*<<< orphan*/  csum_diff; TYPE_1__ locator_match; } ;
struct ila_addr {int /*<<< orphan*/  loc; } ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  compute_csum_diff8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __wsum get_csum_diff_iaddr(struct ila_addr *iaddr, struct ila_params *p)
{
	if (p->locator_match.v64)
		return p->csum_diff;
	else
		return compute_csum_diff8((__be32 *)&p->locator,
					  (__be32 *)&iaddr->loc);
}
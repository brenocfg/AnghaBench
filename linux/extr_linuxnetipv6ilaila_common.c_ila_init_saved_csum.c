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
struct TYPE_2__ {int /*<<< orphan*/  v64; } ;
struct ila_params {TYPE_1__ locator_match; int /*<<< orphan*/  locator; int /*<<< orphan*/  csum_diff; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  compute_csum_diff8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ila_init_saved_csum(struct ila_params *p)
{
	if (!p->locator_match.v64)
		return;

	p->csum_diff = compute_csum_diff8(
				(__be32 *)&p->locator,
				(__be32 *)&p->locator_match);
}
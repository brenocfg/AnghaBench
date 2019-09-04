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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int start; scalar_t__ end; } ;
struct sw_flow_mask {TYPE_1__ range; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_n_bytes (TYPE_1__*) ; 

__attribute__((used)) static bool mask_equal(const struct sw_flow_mask *a,
		       const struct sw_flow_mask *b)
{
	const u8 *a_ = (const u8 *)&a->key + a->range.start;
	const u8 *b_ = (const u8 *)&b->key + b->range.start;

	return  (a->range.end == b->range.end)
		&& (a->range.start == b->range.start)
		&& (memcmp(a_, b_, range_n_bytes(&a->range)) == 0);
}
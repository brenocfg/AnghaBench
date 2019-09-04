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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct fl_flow_mask {TYPE_1__ range; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  rounddown (size_t,int) ; 
 int /*<<< orphan*/  roundup (size_t,int) ; 

__attribute__((used)) static void fl_mask_update_range(struct fl_flow_mask *mask)
{
	const u8 *bytes = (const u8 *) &mask->key;
	size_t size = sizeof(mask->key);
	size_t i, first = 0, last;

	for (i = 0; i < size; i++) {
		if (bytes[i]) {
			first = i;
			break;
		}
	}
	last = first;
	for (i = size - 1; i != first; i--) {
		if (bytes[i]) {
			last = i;
			break;
		}
	}
	mask->range.start = rounddown(first, sizeof(long));
	mask->range.end = roundup(last + 1, sizeof(long));
}
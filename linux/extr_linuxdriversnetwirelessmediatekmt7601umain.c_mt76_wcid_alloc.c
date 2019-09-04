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
struct mt7601u_dev {int /*<<< orphan*/ * wcid_mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int BITS_PER_LONG ; 
 int ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76_wcid_alloc(struct mt7601u_dev *dev)
{
	int i, idx = 0;

	for (i = 0; i < ARRAY_SIZE(dev->wcid_mask); i++) {
		idx = ffs(~dev->wcid_mask[i]);
		if (!idx)
			continue;

		idx--;
		dev->wcid_mask[i] |= BIT(idx);
		break;
	}

	idx = i * BITS_PER_LONG + idx;
	if (idx > 119)
		return -1;

	return idx;
}
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
struct TYPE_2__ {int /*<<< orphan*/ * advertising; int /*<<< orphan*/ * supported; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; } ;

/* Variables and functions */
 unsigned int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 

void ethtool_intersect_link_masks(struct ethtool_link_ksettings *dst,
				  struct ethtool_link_ksettings *src)
{
	unsigned int size = BITS_TO_LONGS(__ETHTOOL_LINK_MODE_MASK_NBITS);
	unsigned int idx = 0;

	for (; idx < size; idx++) {
		dst->link_modes.supported[idx] &=
			src->link_modes.supported[idx];
		dst->link_modes.advertising[idx] &=
			src->link_modes.advertising[idx];
	}
}
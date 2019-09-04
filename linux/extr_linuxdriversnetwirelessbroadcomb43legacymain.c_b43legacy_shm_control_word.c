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
typedef  int u32 ;
typedef  int u16 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_SHM_CONTROL ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline
void b43legacy_shm_control_word(struct b43legacy_wldev *dev,
				u16 routing, u16 offset)
{
	u32 control;

	/* "offset" is the WORD offset. */

	control = routing;
	control <<= 16;
	control |= offset;
	b43legacy_write32(dev, B43legacy_MMIO_SHM_CONTROL, control);
}
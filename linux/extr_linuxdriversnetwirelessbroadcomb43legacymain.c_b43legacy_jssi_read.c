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
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int b43legacy_shm_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 b43legacy_jssi_read(struct b43legacy_wldev *dev)
{
	u32 val = 0;

	val = b43legacy_shm_read16(dev, B43legacy_SHM_SHARED, 0x40A);
	val <<= 16;
	val |= b43legacy_shm_read16(dev, B43legacy_SHM_SHARED, 0x408);

	return val;
}
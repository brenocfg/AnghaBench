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
 int /*<<< orphan*/  B43legacy_SHM_SH_HOSTFHI ; 
 int /*<<< orphan*/  B43legacy_SHM_SH_HOSTFLO ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void b43legacy_hf_write(struct b43legacy_wldev *dev, u32 value)
{
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_HOSTFLO,
			      (value & 0x0000FFFF));
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_HOSTFHI,
			      ((value & 0xFFFF0000) >> 16));
}
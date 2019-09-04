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
typedef  int u64 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  B43_SHM_SH_HOSTF1 ; 
 int /*<<< orphan*/  B43_SHM_SH_HOSTF2 ; 
 int /*<<< orphan*/  B43_SHM_SH_HOSTF3 ; 
 int b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 b43_hf_read(struct b43_wldev *dev)
{
	u64 ret;

	ret = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF3);
	ret <<= 16;
	ret |= b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF2);
	ret <<= 16;
	ret |= b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF1);

	return ret;
}
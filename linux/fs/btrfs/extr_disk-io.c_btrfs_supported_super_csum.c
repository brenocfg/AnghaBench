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
typedef  int u16 ;

/* Variables and functions */
#define  BTRFS_CSUM_TYPE_CRC32 128 

__attribute__((used)) static bool btrfs_supported_super_csum(u16 csum_type)
{
	switch (csum_type) {
	case BTRFS_CSUM_TYPE_CRC32:
		return true;
	default:
		return false;
	}
}
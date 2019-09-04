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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_MAP_LEN_88E ; 
 scalar_t__ Efuse_GetCurrentSize (struct adapter*) ; 

__attribute__((used)) static bool
hal_EfusePgCheckAvailableAddr(
		struct adapter *pAdapter,
		u8 efuseType
	)
{
	if (Efuse_GetCurrentSize(pAdapter) >= EFUSE_MAP_LEN_88E)
		return false;
	return true;
}
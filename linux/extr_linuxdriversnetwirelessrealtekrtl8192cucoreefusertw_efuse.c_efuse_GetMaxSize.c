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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_GetEfuseDefinition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFUSE_WIFI ; 
 int /*<<< orphan*/  TYPE_AVAILABLE_EFUSE_BYTES_TOTAL ; 
 int /*<<< orphan*/  _FALSE ; 

u16 efuse_GetMaxSize(PADAPTER padapter)
{
	u16	max_size;
	EFUSE_GetEfuseDefinition(padapter, EFUSE_WIFI , TYPE_AVAILABLE_EFUSE_BYTES_TOTAL, (PVOID)&max_size, _FALSE);
	return max_size;
}
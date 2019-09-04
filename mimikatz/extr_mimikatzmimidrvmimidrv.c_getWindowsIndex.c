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
typedef  int /*<<< orphan*/  KIWI_OS_INDEX ;

/* Variables and functions */
 int /*<<< orphan*/  KiwiOsIndex_10_1507 ; 
 int /*<<< orphan*/  KiwiOsIndex_10_1511 ; 
 int /*<<< orphan*/  KiwiOsIndex_10_1607 ; 
 int /*<<< orphan*/  KiwiOsIndex_10_1703 ; 
 int /*<<< orphan*/  KiwiOsIndex_10_1709 ; 
 int /*<<< orphan*/  KiwiOsIndex_10_1803 ; 
 int /*<<< orphan*/  KiwiOsIndex_10_1809 ; 
 int /*<<< orphan*/  KiwiOsIndex_2K3 ; 
 int /*<<< orphan*/  KiwiOsIndex_7 ; 
 int /*<<< orphan*/  KiwiOsIndex_8 ; 
 int /*<<< orphan*/  KiwiOsIndex_BLUE ; 
 int /*<<< orphan*/  KiwiOsIndex_UNK ; 
 int /*<<< orphan*/  KiwiOsIndex_VISTA ; 
 int /*<<< orphan*/  KiwiOsIndex_XP ; 
 int* NtBuildNumber ; 

KIWI_OS_INDEX getWindowsIndex()
{
	if(*NtBuildNumber > 17763) // forever 10 =)
		return KiwiOsIndex_10_1809;

	switch(*NtBuildNumber)
	{
		case 2600:
			return KiwiOsIndex_XP;
			break;
		case 3790:	
			return KiwiOsIndex_2K3;
			break;
		case 6000:
		case 6001:
		case 6002:
			return KiwiOsIndex_VISTA;
			break;
		case 7600:
		case 7601:
			return KiwiOsIndex_7;
			break;
		case 8102:
		case 8250:
		case 9200:
			return KiwiOsIndex_8;
		case 9431:
		case 9600:
			return KiwiOsIndex_BLUE;
			break;
		case 10240:
			return KiwiOsIndex_10_1507;
			break;
		case 10586:
			return KiwiOsIndex_10_1511;
			break;
		case 14393:
			return KiwiOsIndex_10_1607;
			break;
		case 15063:
			return KiwiOsIndex_10_1703;
			break;
		case 16299:
			return KiwiOsIndex_10_1709;
			break;
		case 17134:
			return KiwiOsIndex_10_1803;
			break;
		case 17763:
			return KiwiOsIndex_10_1809;
			break;
		default:
			return KiwiOsIndex_UNK;
	}
}
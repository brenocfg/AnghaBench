#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ scan_mode; } ;
struct TYPE_5__ {TYPE_1__ mlmepriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  scalar_t__ RT_SCAN_TYPE ;

/* Variables and functions */
 scalar_t__ SCAN_ACTIVE ; 
 scalar_t__ SCAN_PASSIVE ; 
 int _FAIL ; 
 int _SUCCESS ; 

int rtw_set_scan_mode(_adapter *adapter, RT_SCAN_TYPE scan_mode)
{
	if(scan_mode != SCAN_ACTIVE && scan_mode != SCAN_PASSIVE)
		return _FAIL;
	
	adapter->mlmepriv.scan_mode = scan_mode;

	return _SUCCESS;
}
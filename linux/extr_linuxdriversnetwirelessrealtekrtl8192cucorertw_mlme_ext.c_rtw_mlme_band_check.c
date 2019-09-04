#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ setband; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ GHZ24_50 ; 
 scalar_t__ GHZ_24 ; 
 scalar_t__ GHZ_50 ; 
 int _FALSE ; 
 int _TRUE ; 

bool rtw_mlme_band_check(_adapter *adapter, const u32 ch)
{
	if (adapter->setband == GHZ24_50 /* 2.4G and 5G */
		|| (adapter->setband == GHZ_24 && ch < 35) /* 2.4G only */
		|| (adapter->setband == GHZ_50 && ch > 35) /* 5G only */
	) {
		return _TRUE;
	}
	return _FALSE;
}
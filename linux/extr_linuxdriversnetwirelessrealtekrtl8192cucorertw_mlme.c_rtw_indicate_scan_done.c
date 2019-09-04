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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_os_indicate_scan_done (int /*<<< orphan*/ *,int) ; 

inline void rtw_indicate_scan_done( _adapter *padapter, bool aborted)
{
	rtw_os_indicate_scan_done(padapter, aborted);
}
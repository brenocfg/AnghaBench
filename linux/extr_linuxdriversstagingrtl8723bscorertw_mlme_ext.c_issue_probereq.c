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
struct ndis_802_11_ssid {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _issue_probereq (struct adapter*,struct ndis_802_11_ssid*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

inline void issue_probereq(struct adapter *padapter, struct ndis_802_11_ssid *pssid, u8 *da)
{
	_issue_probereq(padapter, pssid, da, 0, 1, false);
}
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
typedef  int u8 ;

/* Variables and functions */
 int IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FCTL_STYPE ; 
 int IEEE80211_FTYPE_CTL ; 
 int IEEE80211_STYPE_BACK_REQ ; 

__attribute__((used)) static inline int wil_is_back_req(u8 fc)
{
	return (fc & (IEEE80211_FCTL_FTYPE | IEEE80211_FCTL_STYPE)) ==
	       (IEEE80211_FTYPE_CTL | IEEE80211_STYPE_BACK_REQ);
}
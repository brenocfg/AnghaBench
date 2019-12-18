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
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int BSS_MGMT_EN_NEIGHBOR ; 
 int /*<<< orphan*/  __hostapd_bss_mgmt_enable (struct hostapd_data*,int) ; 

__attribute__((used)) static void
hostapd_rrm_nr_enable(struct hostapd_data *hapd)
{
	__hostapd_bss_mgmt_enable(hapd, 1 << BSS_MGMT_EN_NEIGHBOR);
}
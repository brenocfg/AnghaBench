#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ gtk_cipher; int /*<<< orphan*/  ptk_cipher; } ;
struct rsi_common {TYPE_1__ secinfo; } ;

/* Variables and functions */
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 

bool rsi_is_cipher_wep(struct rsi_common *common)
{
	if (((common->secinfo.gtk_cipher == WLAN_CIPHER_SUITE_WEP104) ||
	     (common->secinfo.gtk_cipher == WLAN_CIPHER_SUITE_WEP40)) &&
	    (!common->secinfo.ptk_cipher))
		return true;
	else
		return false;
}
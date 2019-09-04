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
struct ath10k {int dummy; } ;
typedef  enum wmi_txbf_conf { ____Placeholder_wmi_txbf_conf } wmi_txbf_conf ;

/* Variables and functions */
 int WMI_TXBF_CONF_BEFORE_ASSOC ; 

__attribute__((used)) static enum wmi_txbf_conf ath10k_wmi_10_4_txbf_conf_scheme(struct ath10k *ar)
{
	return WMI_TXBF_CONF_BEFORE_ASSOC;
}
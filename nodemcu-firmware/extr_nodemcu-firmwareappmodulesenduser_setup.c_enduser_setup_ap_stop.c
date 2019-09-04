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

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int SOFTAP_MODE ; 
 int wifi_get_opmode () ; 
 int /*<<< orphan*/  wifi_set_opmode (int) ; 

__attribute__((used)) static void enduser_setup_ap_stop(void)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_ap_stop");

  wifi_set_opmode(~SOFTAP_MODE & wifi_get_opmode());
}
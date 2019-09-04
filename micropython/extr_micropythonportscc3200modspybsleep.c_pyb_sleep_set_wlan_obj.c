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
typedef  int /*<<< orphan*/  wlan_obj_t ;
typedef  scalar_t__ mp_obj_t ;
struct TYPE_2__ {int /*<<< orphan*/ * wlan_obj; } ;

/* Variables and functions */
 TYPE_1__ pybsleep_data ; 

void pyb_sleep_set_wlan_obj (mp_obj_t wlan_obj) {
    pybsleep_data.wlan_obj = (wlan_obj_t *)wlan_obj;
}
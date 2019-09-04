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
typedef  int /*<<< orphan*/  ble_evt_t ;

/* Variables and functions */
 int /*<<< orphan*/  ble_ipsp_evt_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_ble_evt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
  ble_ipsp_evt_handler(p_ble_evt);
  on_ble_evt(p_ble_evt);
}
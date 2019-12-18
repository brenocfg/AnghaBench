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
 size_t MG_MAIN_IFACE ; 
 int /*<<< orphan*/  mg_if_create_iface (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mg_ifaces ; 
 int /*<<< orphan*/  test_iface ; 

void tests_setup(void) {
  test_iface = mg_if_create_iface(mg_ifaces[MG_MAIN_IFACE], NULL);
}
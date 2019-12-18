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
 int ADB_DATA_BIT ; 
 int ADB_PORT ; 
 int /*<<< orphan*/  data_hi () ; 
 int /*<<< orphan*/  psw_hi () ; 

void adb_host_init(void) {
    ADB_PORT &= ~(1 << ADB_DATA_BIT);
    data_hi();
#ifdef ADB_PSW_BIT
    psw_hi();
#endif
}
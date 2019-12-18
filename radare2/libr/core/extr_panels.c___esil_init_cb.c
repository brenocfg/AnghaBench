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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __esil_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_refresh_all (int /*<<< orphan*/ *,int,int) ; 

int __esil_init_cb(void *user) {
	RCore *core = (RCore *)user;
	__esil_init (core);
	__set_refresh_all (core, false, false);
	return 0;
}
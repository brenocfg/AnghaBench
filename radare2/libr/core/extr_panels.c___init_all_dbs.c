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
 int /*<<< orphan*/  __init_almighty_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __init_rotate_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __init_sdb (int /*<<< orphan*/ *) ; 

void __init_all_dbs(RCore *core) {
	__init_sdb (core);
	__init_almighty_db (core);
	__init_rotate_db (core);
}
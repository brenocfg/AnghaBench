#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sessions; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 int r_list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_debug_session_lastid(RDebug *dbg) {
	return r_list_length (dbg->sessions);
}
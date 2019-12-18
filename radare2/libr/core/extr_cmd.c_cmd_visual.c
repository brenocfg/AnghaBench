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
struct TYPE_3__ {scalar_t__ http_up; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_is_interactive () ; 
 int r_core_visual (TYPE_1__*,char const*) ; 

__attribute__((used)) static int cmd_visual(void *data, const char *input) {
	RCore *core = (RCore*) data;
	if (core->http_up) {
		return false;
	}
	if (!r_cons_is_interactive ()) {
		return false;
	}
	return r_core_visual ((RCore *)data, input);
}
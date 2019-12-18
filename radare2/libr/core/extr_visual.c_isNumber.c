#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* print; } ;
struct TYPE_4__ {scalar_t__ cur_enabled; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */

__attribute__((used)) static bool isNumber(RCore *core, int ch) {
	if (ch > '0' && ch <= '9') {
		return true;
	}
	if (core->print->cur_enabled) {
		return ch == '0';
	}
	return false;
}
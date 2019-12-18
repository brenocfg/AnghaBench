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
struct TYPE_2__ {int mouse; } ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_enable_mouse (int) ; 
 TYPE_1__* r_cons_singleton () ; 

__attribute__((used)) static bool __holdMouseState(RCore *core) {
	bool m = r_cons_singleton ()->mouse;
	r_cons_enable_mouse (false);
	return m;
}
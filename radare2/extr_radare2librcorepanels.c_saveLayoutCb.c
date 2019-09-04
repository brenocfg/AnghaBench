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
struct TYPE_2__ {int /*<<< orphan*/  panels; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_any_key (char const*) ; 
 int /*<<< orphan*/  savePanelsLayout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saveLayoutCb(void *user) {
	RCore *core = (RCore *)user;
	savePanelsLayout (core->panels);
	const char *msg = "Panels layout saved!";
	(void)r_cons_any_key (msg);
	return 0;
}
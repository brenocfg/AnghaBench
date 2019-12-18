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
struct r_anal_t {TYPE_1__* user; } ;
struct TYPE_3__ {scalar_t__ cfglog; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_log_add (TYPE_1__*,char const*) ; 

__attribute__((used)) static bool r_core_anal_log(struct r_anal_t *anal, const char *msg) {
	RCore *core = anal->user;
	if (core->cfglog) {
		r_core_log_add (core, msg);
	}
	return true;
}
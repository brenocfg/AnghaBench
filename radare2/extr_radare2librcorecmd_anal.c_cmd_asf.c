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
struct TYPE_5__ {TYPE_1__* anal; } ;
struct TYPE_4__ {int /*<<< orphan*/  sdb_fcnsign; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 
 char* sdb_querys (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void cmd_asf(RCore *core, const char *input) {
	char *ret;
	if (input[0] == ' ') {
		ret = sdb_querys (core->anal->sdb_fcnsign, NULL, 0, input + 1);
	} else {
		ret = sdb_querys (core->anal->sdb_fcnsign, NULL, 0, "*");
	}
	if (ret && *ret) {
		r_cons_println (ret);
	}
	free (ret);
}
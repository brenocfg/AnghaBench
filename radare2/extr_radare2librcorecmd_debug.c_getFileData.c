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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  rcmd; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 scalar_t__ r_cmd_alias_get (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ r_file_slurp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut8*getFileData(RCore *core, const char *arg) {
	if (*arg == '$') {
		return (ut8*) r_cmd_alias_get (core->rcmd, arg, 1);
	}
	return (ut8*)r_file_slurp (arg, NULL);
}
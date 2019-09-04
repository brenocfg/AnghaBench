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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_num_get (int /*<<< orphan*/ ,char const*) ; 
 int r_sign_add_addr (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* r_str_word_get0 (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool addOffsetZign(RCore *core, const char *name, const char *args0, int nargs) {
	const char *offstr = NULL;
	ut64 offset = UT64_MAX;

	if (nargs != 1) {
		eprintf ("error: invalid syntax\n");
		return false;
	}

	offstr = r_str_word_get0 (args0, 0);
	offset = r_num_get (core->num, offstr);

	return r_sign_add_addr (core->anal, name, offset);
}
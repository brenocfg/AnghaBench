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
struct TYPE_4__ {char* (* system ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  io; } ;
struct TYPE_5__ {int /*<<< orphan*/  anal; TYPE_1__ iob; } ;
typedef  TYPE_2__ RDebug ;

/* Variables and functions */
 char* r_anal_get_reg_profile (int /*<<< orphan*/ ) ; 
 char* r_cons_get_buffer () ; 
 int /*<<< orphan*/  r_cons_pop () ; 
 int /*<<< orphan*/  r_cons_push () ; 
 char* strdup (char const*) ; 
 char* stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *__io_reg_profile(RDebug *dbg) {
	r_cons_push ();
	char *drp = dbg->iob.system (dbg->iob.io, "drp");
	if (drp) {
		return drp;
	}
	const char *buf = r_cons_get_buffer ();
	if (buf && *buf) {
		char *ret = strdup (buf);
		r_cons_pop ();
		return ret;
	}
	return r_anal_get_reg_profile (dbg->anal);
}
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
struct TYPE_4__ {int /*<<< orphan*/  sdb_types; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,...) ; 
 int /*<<< orphan*/  r_core_cmdf (TYPE_2__*,char*,char*,char const*) ; 
 char* r_type_format (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int print_link_readable_json_cb(void *p, const char *k, const char *v) {
	RCore *core = (RCore *)p;
	char *fmt = r_type_format (core->anal->sdb_types, v);
	if (!fmt) {
		eprintf ("Can't fint type %s", v);
		return 1;
	}
	r_cons_printf ("{\"%s\":", v);
	r_core_cmdf (core, "pfj %s @ 0x%s\n", fmt, k + strlen ("link."));
	r_cons_printf ("}");
	return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  namefmt ;
struct TYPE_5__ {int /*<<< orphan*/  (* cb_printf ) (char*,char const*) ;int /*<<< orphan*/  sdb_types; int /*<<< orphan*/  formats; } ;
typedef  TYPE_1__ RPrint ;

/* Variables and functions */
 scalar_t__ MUSTSEE ; 
 int NESTDEPTH ; 
 int /*<<< orphan*/  SEEVALUE ; 
 int STRUCTFLAG ; 
 int STRUCTPTR ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  r_print_format (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,char const*,int,char const*,char*) ; 
 int r_print_format_struct_size (TYPE_1__*,char const*,int,int /*<<< orphan*/ ) ; 
 char* r_type_format (int /*<<< orphan*/ ,char const*) ; 
 char* sdb_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (char*,char*) ; 
 int /*<<< orphan*/  stub2 (char*,char*) ; 
 int /*<<< orphan*/  stub3 (char*,char const*) ; 

__attribute__((used)) static int r_print_format_struct(RPrint* p, ut64 seek, const ut8* b, int len, const char *name,
		int slide, int mode, const char *setval, char *field, int anon) {
	const char *fmt;
	char namefmt[128];
	slide++;
	if ((slide % STRUCTPTR) > NESTDEPTH || (slide % STRUCTFLAG)/STRUCTPTR > NESTDEPTH) {
		eprintf ("Too much nested struct, recursion too deep...\n");
		return 0;
	}
	if (anon) {
		fmt = name;
	} else {
		fmt = sdb_get (p->formats, name, NULL);
		if (!fmt) { // Fetch struct info from types DB
			fmt = r_type_format (p->sdb_types, name);
		}
	}
	if (!fmt || !*fmt) {
		eprintf ("Undefined struct '%s'.\n", name);
		return 0;
	}
	if (MUSTSEE && !SEEVALUE) {
		snprintf (namefmt, sizeof (namefmt), "%%%ds", 10+6*slide%STRUCTPTR);
		if (fmt[0] == '0') {
			p->cb_printf (namefmt, "union");
		} else {
			p->cb_printf (namefmt, "struct");
		}
		p->cb_printf ("<%s>\n", name);
	}
	r_print_format (p, seek, b, len, fmt, mode, setval, field);
	return r_print_format_struct_size (p, fmt, mode, 0);
}
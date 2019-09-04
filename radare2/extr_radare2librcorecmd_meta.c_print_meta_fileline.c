#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* bin; } ;
struct TYPE_6__ {TYPE_1__* cur; } ;
struct TYPE_5__ {int /*<<< orphan*/  sdb_addrinfo; } ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_printf (char*,char const*) ; 
 char* sdb_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int print_meta_fileline(RCore *core, const char *file_line) {
	char *meta_info = sdb_get (core->bin->cur->sdb_addrinfo, file_line, 0);
	if (meta_info) {
		r_cons_printf ("Meta info %s\n", meta_info);
	} else {
		r_cons_printf ("No meta info for %s found\n", file_line);
	}
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_9__ {TYPE_1__* esil; } ;
struct TYPE_8__ {TYPE_3__* anal; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {scalar_t__ address; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_REF_TYPE_DATA ; 
 int /*<<< orphan*/  R_FLAGS_FS_STRINGS ; 
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 char* is_string_at (TYPE_2__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  r_anal_xrefs_set (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_flag_set (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  r_flag_space_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_flag_space_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_meta_add (TYPE_3__*,char,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_name_filter (char*,int) ; 
 char* sdb_fmt (char*,char*) ; 

__attribute__((used)) static void add_string_ref(RCore *core, ut64 xref_from, ut64 xref_to) {
	int len = 0;
	if (xref_to == UT64_MAX || !xref_to) {
		return;
	}
	if (!xref_from || xref_from == UT64_MAX) {
		xref_from = core->anal->esil->address;
	}
	char *str_flagname = is_string_at (core, xref_to, &len);
	if (str_flagname) {
		r_anal_xrefs_set (core->anal, xref_from, xref_to, R_ANAL_REF_TYPE_DATA);
		r_name_filter (str_flagname, -1);
		char *flagname = sdb_fmt ("str.%s", str_flagname);
		r_flag_space_push (core->flags, R_FLAGS_FS_STRINGS);
		r_flag_set (core->flags, flagname, xref_to, len);
		r_flag_space_pop (core->flags);
		r_meta_add (core->anal, 's', xref_to, xref_to + len, str_flagname);
		free (str_flagname);
	}
}
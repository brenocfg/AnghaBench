#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RBinSymbol ;

/* Variables and functions */
 int /*<<< orphan*/  R_BIN_TYPE_SECTION_STR ; 
 int /*<<< orphan*/  R_FLAGS_FS_IMPORTS ; 
 int /*<<< orphan*/  R_FLAGS_FS_SYMBOLS ; 
 int /*<<< orphan*/  R_FLAGS_FS_SYMBOLS_SECTIONS ; 
 int /*<<< orphan*/  r_flag_space_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void select_flag_space(RCore *core, RBinSymbol *symbol) {
	if (!strncmp (symbol->name, "imp.", 4)) {
		r_flag_space_push (core->flags, R_FLAGS_FS_IMPORTS);
	} else if (symbol->type && !strcmp (symbol->type, R_BIN_TYPE_SECTION_STR)) {
		r_flag_space_push (core->flags, R_FLAGS_FS_SYMBOLS_SECTIONS);
	} else {
		r_flag_space_push (core->flags, R_FLAGS_FS_SYMBOLS);
	}
}
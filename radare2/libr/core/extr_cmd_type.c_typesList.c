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
struct TYPE_6__ {TYPE_1__* anal; } ;
struct TYPE_5__ {int /*<<< orphan*/  sdb_types; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  print_keys (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_typelist_json_cb ; 
 int /*<<< orphan*/  print_typelist_r_cb ; 
 int /*<<< orphan*/  printkey_cb ; 
 int /*<<< orphan*/ * stdiftype ; 

__attribute__((used)) static void typesList(RCore *core, int mode) {
	switch (mode) {
	case 1:
	case '*':
		print_keys (core->anal->sdb_types, core, NULL, print_typelist_r_cb, false);
		break;
	case 'j':
		print_keys (core->anal->sdb_types, core, stdiftype, print_typelist_json_cb, true);
		break;
	default:
		print_keys (core->anal->sdb_types, core, stdiftype, printkey_cb, false);
		break;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* anal; } ;
struct TYPE_3__ {int /*<<< orphan*/  sdb_types; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_type_del (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdbdeletelink(void *p, const char *k, const char *v) {
	RCore *core = (RCore *)p;
	if (!strncmp (k, "link.", strlen ("link."))) {
		r_type_del (core->anal->sdb_types, k);
	}
	return 1;
}
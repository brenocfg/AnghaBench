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
struct TYPE_5__ {TYPE_1__* panels; } ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ RPanels ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 char* sdb_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

char *__search_db(RCore *core, const char *title) {
	RPanels *panels = core->panels;
	if (!panels->db) {
		return NULL;
	}
	char *out = sdb_get (panels->db, title, 0);
	if (out) {
		return out;
	}
	return NULL;
}
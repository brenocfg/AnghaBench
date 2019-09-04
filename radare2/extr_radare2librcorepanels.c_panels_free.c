#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mht; int /*<<< orphan*/  rotate_db; int /*<<< orphan*/  db; int /*<<< orphan*/  can; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** panels; } ;
typedef  TYPE_1__ RPanelsRoot ;
typedef  TYPE_2__ RPanels ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  freeAllPanels (TYPE_2__*) ; 
 int /*<<< orphan*/  ht_pp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_canvas_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_switchbuf (int) ; 
 int /*<<< orphan*/  sdb_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panels_free(RPanelsRoot *panels_root, int i, RPanels *panels) {
	r_cons_switchbuf (true);
	if (panels) {
		freeAllPanels (panels);
		r_cons_canvas_free (panels->can);
		sdb_free (panels->db);
		sdb_free (panels->rotate_db);
		ht_pp_free (panels->mht);
		free (panels);
		panels_root->panels[i] = NULL;
	}
}
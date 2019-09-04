#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* panels_root; } ;
struct TYPE_6__ {int cur_panels; int n_panels; int /*<<< orphan*/ * panels; } ;
typedef  TYPE_1__ RPanelsRoot ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  get_cur_panels (TYPE_1__*) ; 
 int /*<<< orphan*/  panels_free (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_panels(RCore *core) {
	RPanelsRoot *panels_root = core->panels_root;
	panels_free (panels_root, panels_root->cur_panels, get_cur_panels (panels_root));
	int i;
	for (i = panels_root->cur_panels; i < panels_root->n_panels - 1; i++) {
		panels_root->panels[i] = panels_root->panels[i + 1];
	}
	panels_root->n_panels--;
	if (panels_root->cur_panels >= panels_root->n_panels) {
		panels_root->cur_panels = panels_root->n_panels - 1;
	}
}
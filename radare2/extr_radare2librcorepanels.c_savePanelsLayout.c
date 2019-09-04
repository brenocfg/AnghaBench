#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* model; TYPE_2__* view; } ;
struct TYPE_12__ {int n_panels; } ;
struct TYPE_11__ {int /*<<< orphan*/  cache; int /*<<< orphan*/  cmd; int /*<<< orphan*/  title; } ;
struct TYPE_9__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {TYPE_1__ pos; } ;
typedef  TYPE_4__ RPanels ;
typedef  TYPE_5__ RPanel ;
typedef  int /*<<< orphan*/  PJ ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_5__* getPanel (TYPE_4__*,int) ; 
 char* getPanelsConfigPath () ; 
 int /*<<< orphan*/  pj_a (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_kb (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pj_kn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 char* pj_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_sandbox_fopen (char*,char*) ; 

__attribute__((used)) static void savePanelsLayout(RPanels* panels) {
	int i;
	PJ *pj = NULL;
	pj = pj_new ();
	pj_a (pj);
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *panel = getPanel (panels, i);
		pj_o (pj);
		pj_ks (pj, "Title", panel->model->title);
		pj_ks (pj, "Cmd", panel->model->cmd);
		pj_kn (pj, "x", panel->view->pos.x);
		pj_kn (pj, "y", panel->view->pos.y);
		pj_kn (pj, "w", panel->view->pos.w);
		pj_kn (pj, "h", panel->view->pos.h);
		pj_kb (pj, "cache", panel->model->cache);
		pj_end (pj);
	}
	pj_end (pj);
	char *configPath = getPanelsConfigPath ();
	FILE *panelsConfig = r_sandbox_fopen (configPath, "w");
	free (configPath);
	if (panelsConfig) {
		fprintf (panelsConfig, "%s", pj_string (pj));
		fclose (panelsConfig);
	}
	pj_free (pj);
}
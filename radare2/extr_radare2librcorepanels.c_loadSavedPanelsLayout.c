#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_4__* panels; } ;
struct TYPE_19__ {TYPE_3__* model; TYPE_2__* view; } ;
struct TYPE_18__ {scalar_t__ n_panels; scalar_t__ curnode; } ;
struct TYPE_17__ {void* cmd; void* title; } ;
struct TYPE_15__ {void* h; void* w; void* y; void* x; } ;
struct TYPE_16__ {TYPE_1__ pos; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_4__ RPanels ;
typedef  TYPE_5__ RPanel ;
typedef  TYPE_6__ RCore ;

/* Variables and functions */
 void* atoi (char*) ; 
 int /*<<< orphan*/  buildPanelParam (TYPE_6__*,TYPE_5__*,char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_5__* getPanel (TYPE_4__*,scalar_t__) ; 
 char* getPanelsConfigPath () ; 
 int /*<<< orphan*/  help_msg_panels ; 
 int /*<<< orphan*/  panelAllClear (TYPE_4__*) ; 
 char* parsePanelsConfig (char*,scalar_t__) ; 
 int /*<<< orphan*/  r_core_visual_append_help (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* r_file_slurp (char*,int*) ; 
 int /*<<< orphan*/  r_str_arg_unescape (char*) ; 
 void* r_str_dup (void*,char*) ; 
 scalar_t__ r_str_endswith (char*,char*) ; 
 int r_str_split (char*,char) ; 
 int /*<<< orphan*/  r_strbuf_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (int /*<<< orphan*/ *) ; 
 int sdb_json_get_bool (char*,char*) ; 
 char* sdb_json_get_str (char*,char*) ; 
 int /*<<< orphan*/  setReadOnly (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_4__*,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int loadSavedPanelsLayout(RCore *core) {
	int i, s;
	char *panelsConfig;

	char *configPath = getPanelsConfigPath ();
	panelsConfig = r_file_slurp (configPath, &s);
	free (configPath);
	if (!panelsConfig) {
		free (panelsConfig);
		return 0;
	}
	char *parsedConfig = parsePanelsConfig (panelsConfig, strlen (panelsConfig));
	free (panelsConfig);
	if (!parsedConfig) {
		return 0;
	}
	int count = r_str_split (parsedConfig, '\n');
	RPanels *panels = core->panels;
	panelAllClear (panels);
	panels->n_panels = 0;
	panels->curnode = 0;
	char *title, *cmd, *x, *y, *w, *h, *p_cfg = parsedConfig;
	bool cache;
	for (i = 1; i < count; i++) {
		title = sdb_json_get_str (p_cfg, "Title");
		cmd = sdb_json_get_str (p_cfg, "Cmd");
		(void)r_str_arg_unescape (cmd);
		x = sdb_json_get_str (p_cfg, "x");
		y = sdb_json_get_str (p_cfg, "y");
		w = sdb_json_get_str (p_cfg, "w");
		h = sdb_json_get_str (p_cfg, "h");
		cache = sdb_json_get_bool (p_cfg, "cache");
		RPanel *p = getPanel (panels, panels->n_panels);
		p->view->pos.x = atoi (x);
		p->view->pos.y = atoi (y);
		p->view->pos.w = atoi (w);
		p->view->pos.h = atoi (h);
		buildPanelParam(core, p, title, cmd, cache);
		//TODO: Super hacky and refactoring is needed
		if (r_str_endswith (cmd, "Help")) {
			p->model->title = r_str_dup (p->model->title, "Help");
			p->model->cmd = r_str_dup (p->model->cmd, "Help");
			RStrBuf *rsb = r_strbuf_new (NULL);
			r_core_visual_append_help (rsb, "Visual Ascii Art Panels", help_msg_panels);
			if (!rsb) {
				return 0;
			}
			setReadOnly (p, r_strbuf_drain (rsb));
		}
		p_cfg += strlen (p_cfg) + 1;
	}
	free (parsedConfig);
	if (!panels->n_panels) {
		return 0;
	}
	setRefreshAll (core->panels, true);
	return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_3__* panels; } ;
struct TYPE_19__ {TYPE_2__* model; TYPE_1__* view; } ;
struct TYPE_18__ {scalar_t__ n_panels; } ;
struct TYPE_17__ {void* cmd; void* title; } ;
struct TYPE_16__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 scalar_t__ R_STR_ISEMPTY (char*) ; 
 TYPE_4__* __get_panel (TYPE_3__*,scalar_t__) ; 
 char* __get_panels_config_file_from_dir (char const*) ; 
 int /*<<< orphan*/  __init_panel_param (TYPE_5__*,TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  __panel_all_clear (TYPE_3__*) ; 
 char* __parse_panels_config (char*,scalar_t__) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_geometry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_read_only (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  __show_status (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_panels ; 
 int /*<<< orphan*/  r_core_visual_append_help (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* r_file_slurp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_str_arg_unescape (char*) ; 
 void* r_str_dup (void*,char*) ; 
 scalar_t__ r_str_endswith (char*,char*) ; 
 char* r_str_newf (char*,char const*) ; 
 int r_str_split (char*,char) ; 
 int /*<<< orphan*/  r_strbuf_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (int /*<<< orphan*/ *) ; 
 char* sdb_json_get_str (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

bool r_load_panels_layout(RCore *core, const char *_name) {
	if (!core->panels) {
		return false;
	}
	char *config_path = __get_panels_config_file_from_dir (_name);
	if (!config_path) {
		char *tmp = r_str_newf ("No saved layout found for the name: %s", _name);
		(void)__show_status (core, tmp);
		free (tmp);
		return false;
	}
	char *panels_config = r_file_slurp (config_path, NULL);
	free (config_path);
	if (!panels_config) {
		char *tmp = r_str_newf ("Layout is empty: %s", _name);
		(void)__show_status (core, tmp);
		free (tmp);
		return false;
	}
	RPanels *panels = core->panels;
	__panel_all_clear (panels);
	panels->n_panels = 0;
	__set_curnode (core, 0);
	char *title, *cmd, *x, *y, *w, *h, *p_cfg = panels_config, *tmp_cfg;
	int i, tmp_count;
	tmp_cfg = __parse_panels_config (p_cfg, strlen (p_cfg));
	tmp_count = r_str_split (tmp_cfg, '\n');
	for (i = 0; i < tmp_count; i++) {
		if (R_STR_ISEMPTY (tmp_cfg)) {
			break;
		}
		title = sdb_json_get_str (tmp_cfg, "Title");
		cmd = sdb_json_get_str (tmp_cfg, "Cmd");
		(void)r_str_arg_unescape (cmd);
		x = sdb_json_get_str (tmp_cfg, "x");
		y = sdb_json_get_str (tmp_cfg, "y");
		w = sdb_json_get_str (tmp_cfg, "w");
		h = sdb_json_get_str (tmp_cfg, "h");
		RPanel *p = __get_panel (panels, panels->n_panels);
		__set_geometry (&p->view->pos, atoi (x), atoi (y), atoi (w),atoi (h));
		__init_panel_param (core, p, title, cmd);
		if (r_str_endswith (cmd, "Help")) {
			p->model->title = r_str_dup (p->model->title, "Help");
			p->model->cmd = r_str_dup (p->model->cmd, "Help");
			RStrBuf *rsb = r_strbuf_new (NULL);
			r_core_visual_append_help (rsb, "Visual Ascii Art Panels", help_msg_panels);
			if (!rsb) {
				return false;
			}
			__set_read_only (p, r_strbuf_drain (rsb));
		}
		tmp_cfg += strlen (tmp_cfg) + 1;
	}
	p_cfg += strlen (p_cfg) + 1;
	free (panels_config);
	if (!panels->n_panels) {
		return false;
	}
	__set_refresh_all (core, true, false);
	return true;
}
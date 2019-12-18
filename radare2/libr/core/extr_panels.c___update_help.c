#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* view; TYPE_1__* model; } ;
struct TYPE_11__ {int n_panels; int mode; } ;
struct TYPE_10__ {int refresh; } ;
struct TYPE_9__ {void* cmd; void* title; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;

/* Variables and functions */
#define  PANEL_MODE_WINDOW 129 
#define  PANEL_MODE_ZOOM 128 
 TYPE_4__* __get_panel (TYPE_3__*,int) ; 
 int /*<<< orphan*/  __set_read_only (TYPE_4__*,int /*<<< orphan*/ ) ; 
 char** help_msg_panels ; 
 char** help_msg_panels_window ; 
 char** help_msg_panels_zoom ; 
 int /*<<< orphan*/  r_core_visual_append_help (int /*<<< orphan*/ *,char const*,char const**) ; 
 void* r_str_dup (void*,char const*) ; 
 scalar_t__ r_str_endswith (void*,char*) ; 
 int /*<<< orphan*/  r_strbuf_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (int /*<<< orphan*/ *) ; 

void __update_help(RPanels *ps) {
	int i;
	for (i = 0; i < ps->n_panels; i++) {
		RPanel *p = __get_panel (ps, i);
		if (r_str_endswith (p->model->cmd, "Help")) {
			RStrBuf *rsb = r_strbuf_new (NULL);
			const char *title, *cmd;
			const char **msg;
			switch (ps->mode) {
				case PANEL_MODE_WINDOW:
					title = "Panels Window mode help";
					cmd = "Window Mode Help";
					msg = help_msg_panels_window;
					break;
				case PANEL_MODE_ZOOM:
					title = "Panels Zoom mode help";
					cmd = "Zoom Mode Help";
					msg = help_msg_panels_zoom;
					break;
				default:
					title = "Visual Ascii Art Panels";
					cmd = "Help";
					msg = help_msg_panels;
					break;
			}
			p->model->title = r_str_dup (p->model->title, cmd);
			p->model->cmd = r_str_dup (p->model->cmd, cmd);
			r_core_visual_append_help (rsb, title, msg);
			if (!rsb) {
				return;
			}
			__set_read_only (p, r_strbuf_drain (rsb));
			p->view->refresh = true;
		}
	}
}
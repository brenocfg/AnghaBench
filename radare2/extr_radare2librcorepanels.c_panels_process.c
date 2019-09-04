#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_98__   TYPE_9__ ;
typedef  struct TYPE_97__   TYPE_8__ ;
typedef  struct TYPE_96__   TYPE_7__ ;
typedef  struct TYPE_95__   TYPE_6__ ;
typedef  struct TYPE_94__   TYPE_5__ ;
typedef  struct TYPE_93__   TYPE_4__ ;
typedef  struct TYPE_92__   TYPE_3__ ;
typedef  struct TYPE_91__   TYPE_2__ ;
typedef  struct TYPE_90__   TYPE_1__ ;
typedef  struct TYPE_89__   TYPE_10__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_98__ {int vmode; TYPE_7__* panels; TYPE_5__* print; TYPE_4__* cons; int /*<<< orphan*/  config; int /*<<< orphan*/  offset; int /*<<< orphan*/  num; int /*<<< orphan*/  dbg; TYPE_6__* panels_root; } ;
struct TYPE_97__ {TYPE_3__* model; TYPE_2__* view; } ;
struct TYPE_96__ {scalar_t__ fun; scalar_t__ mode; TYPE_10__* can; int /*<<< orphan*/  curnode; void* autoUpdate; } ;
struct TYPE_95__ {int n_panels; } ;
struct TYPE_94__ {int cur; int cur_enabled; scalar_t__ col; } ;
struct TYPE_93__ {TYPE_9__* event_data; int /*<<< orphan*/ * event_resize; } ;
struct TYPE_92__ {int /*<<< orphan*/  cache; int /*<<< orphan*/  cmd; int /*<<< orphan*/  title; int /*<<< orphan*/  (* rotateCb ) (TYPE_9__*,int) ;int /*<<< orphan*/  (* directionCb ) (TYPE_9__*,int) ;int /*<<< orphan*/  addr; } ;
struct TYPE_90__ {int h; int w; } ;
struct TYPE_91__ {int refresh; TYPE_1__ pos; } ;
struct TYPE_89__ {int color; } ;
typedef  TYPE_6__ RPanelsRoot ;
typedef  TYPE_7__ RPanels ;
typedef  TYPE_8__ RPanel ;
typedef  TYPE_9__ RCore ;
typedef  int /*<<< orphan*/ * RConsEvent ;
typedef  TYPE_10__ RConsCanvas ;

/* Variables and functions */
 scalar_t__ DOWN ; 
 scalar_t__ LEFT ; 
 char* PANEL_CMD_DISASSEMBLY ; 
 char* PANEL_CMD_GRAPH ; 
 void* PANEL_FUN_NOFUN ; 
 scalar_t__ PANEL_FUN_SAKURA ; 
 scalar_t__ PANEL_FUN_SNOW ; 
 scalar_t__ PANEL_MODE_MENU ; 
 scalar_t__ PANEL_MODE_WINDOW ; 
 scalar_t__ PANEL_MODE_ZOOM ; 
 char* PANEL_TITLE_DECOMPILER ; 
 char* PANEL_TITLE_DISASSEMBLY ; 
 char* PANEL_TITLE_GRAPH ; 
 scalar_t__ RIGHT ; 
#define  R_CONS_KEY_F1 139 
#define  R_CONS_KEY_F10 138 
#define  R_CONS_KEY_F11 137 
#define  R_CONS_KEY_F12 136 
#define  R_CONS_KEY_F2 135 
#define  R_CONS_KEY_F3 134 
#define  R_CONS_KEY_F4 133 
#define  R_CONS_KEY_F5 132 
#define  R_CONS_KEY_F6 131 
#define  R_CONS_KEY_F7 130 
#define  R_CONS_KEY_F8 129 
#define  R_CONS_KEY_F9 128 
 scalar_t__ UP ; 
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  activateCursor (TYPE_9__*) ; 
 int /*<<< orphan*/  addNewPanel (TYPE_9__*,char*,char*,int) ; 
 int /*<<< orphan*/  callVisualGraph (TYPE_9__*) ; 
 int /*<<< orphan*/  checkFunc (TYPE_9__*) ; 
 int /*<<< orphan*/  checkPanelNum (TYPE_7__*) ; 
 int /*<<< orphan*/  clearPanelsMenu (TYPE_9__*) ; 
 int /*<<< orphan*/  createDefaultPanels (TYPE_9__*) ; 
 TYPE_10__* createNewCanvas (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  doPanelsRefresh (TYPE_9__*) ; 
 scalar_t__ doPanelsRefreshOneShot ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_8__* getCurPanel (TYPE_7__*) ; 
 int /*<<< orphan*/  handleComment (TYPE_9__*) ; 
 scalar_t__ handleCursorMode (TYPE_9__*,int) ; 
 int /*<<< orphan*/  handleMenu (TYPE_9__*,int) ; 
 int /*<<< orphan*/  handleTabKey (TYPE_9__*,int) ; 
 scalar_t__ handleWindowMode (TYPE_9__*,int) ; 
 scalar_t__ handleZoomMode (TYPE_9__*,int) ; 
 int /*<<< orphan*/  handle_tab (TYPE_9__*) ; 
 int /*<<< orphan*/  hudstuff (TYPE_9__*) ; 
 int /*<<< orphan*/  initPanels (TYPE_9__*,TYPE_7__*) ; 
 int /*<<< orphan*/  initPanelsMenu (TYPE_9__*) ; 
 int /*<<< orphan*/  panelBreakpoint (TYPE_9__*) ; 
 int /*<<< orphan*/  panelContinue (TYPE_9__*) ; 
 int /*<<< orphan*/  panelSingleStepIn (TYPE_9__*) ; 
 int /*<<< orphan*/  panelSingleStepOver (TYPE_9__*) ; 
 int /*<<< orphan*/  panels_layout (TYPE_7__*) ; 
 int /*<<< orphan*/  panels_layout_refresh (TYPE_9__*) ; 
 TYPE_7__* panels_new (TYPE_9__*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 int r_cons_arrow_to_hjkl (int) ; 
 int /*<<< orphan*/  r_cons_canvas_free (TYPE_10__*) ; 
 int /*<<< orphan*/  r_cons_enable_mouse (int) ; 
 int r_cons_get_size (int*) ; 
 char* r_cons_input (char*) ; 
 int r_cons_readchar () ; 
 int r_cons_readchar_timeout (int) ; 
 int /*<<< orphan*/  r_cons_switchbuf (int) ; 
 void* r_cons_yesno (char,char*) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_9__*,char const*) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_seek_next (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  r_core_seek_previous (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  r_core_visual_asm (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_browse (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_core_visual_define (TYPE_9__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_hud (TYPE_9__*) ; 
 int /*<<< orphan*/  r_core_visual_jump (TYPE_9__*,int) ; 
 int /*<<< orphan*/  r_core_visual_offset (TYPE_9__*) ; 
 int /*<<< orphan*/  r_core_visual_prompt_input (TYPE_9__*) ; 
 int /*<<< orphan*/  r_core_visual_refs (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  r_core_visual_showcursor (TYPE_9__*,int) ; 
 int /*<<< orphan*/  r_debug_reg_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_num_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  redoSeek (TYPE_9__*) ; 
 int /*<<< orphan*/  replaceCmd (TYPE_9__*,char*,char*,int) ; 
 int /*<<< orphan*/  resetScrollPos (TYPE_8__*) ; 
 int /*<<< orphan*/  resetSnow (TYPE_7__*) ; 
 int /*<<< orphan*/  reset_filter (TYPE_8__*) ; 
 int /*<<< orphan*/  rotateAsmemu (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  rotatePanels (TYPE_7__*,int) ; 
 int /*<<< orphan*/  setMode (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_7__*,int) ; 
 int /*<<< orphan*/  set_filter (TYPE_8__*) ; 
 int /*<<< orphan*/  splitPanelHorizontal (TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splitPanelVertical (TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub10 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub9 (TYPE_9__*,int) ; 
 int /*<<< orphan*/  swapPanels (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toggleCache (TYPE_8__*) ; 
 int /*<<< orphan*/  toggleHelp (TYPE_9__*) ; 
 int /*<<< orphan*/  toggleWindowMode (TYPE_7__*) ; 
 int /*<<< orphan*/  toggleZoomMode (TYPE_7__*) ; 
 int /*<<< orphan*/  undoSeek (TYPE_9__*) ; 

__attribute__((used)) static int panels_process(RCore *core, RPanels **r_panels, bool *force_quit) {
	int i, okey, key;
	bool first_load = !*r_panels;
    RPanelsRoot *panels_root = core->panels_root;
	RPanels *panels;
	RPanels *prev;
	if (!*r_panels) {
		panels = panels_new (core);
		if (!panels) {
			return true;
		}
		prev = core->panels;
		core->panels = panels;
		if (!initPanelsMenu (core)) {
			return true;
		}
		if (!initPanels (core, panels)) {
			return true;
		}
		*r_panels = panels;
	} else {
		prev = core->panels;
		panels = *r_panels;
		core->panels = panels;
	}

	r_cons_switchbuf (false);

	int originCursor = core->print->cur;
	core->print->cur = 0;
	core->print->cur_enabled = false;
	core->print->col = 0;

	bool originVmode = core->vmode;
	core->vmode = true;

	r_cons_enable_mouse (false);

	if (first_load) {
		createDefaultPanels (core);
		panels_layout (panels);
	}
repeat:
	core->panels = panels;
	core->cons->event_resize = NULL; // avoid running old event with new data
	core->cons->event_data = core;
	core->cons->event_resize = (RConsEvent) doPanelsRefreshOneShot;
	panels_layout_refresh (core);
	RPanel *cur = getCurPanel (panels);
	if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
		if (panels->mode != PANEL_MODE_MENU) {
			okey = r_cons_readchar_timeout (300);
			if (okey == -1) {
				cur->view->refresh = true;
				goto repeat;
			}
		} else {
			panels->fun = PANEL_FUN_NOFUN;
			resetSnow (panels);
			setRefreshAll (panels, false);
			goto repeat;
		}
	} else {
		okey = r_cons_readchar ();
	}
	key = r_cons_arrow_to_hjkl (okey);
	r_cons_switchbuf (true);

	if (panels->mode == PANEL_MODE_MENU) {
		if (!handleMenu (core, key)) {
			goto exit;
		}
		goto repeat;
	}

	if (core->print->cur_enabled) {
		if (handleCursorMode (core, key)) {
			goto repeat;
		}
	}

	if (panels->mode == PANEL_MODE_ZOOM) {
		if (handleZoomMode (core, key)) {
			goto repeat;
		}
	}

	if (panels->mode == PANEL_MODE_WINDOW) {
		if (handleWindowMode (core, key)) {
			goto repeat;
		}
	}

	if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
				strcmp (cur->model->cmd, "pdc") && '0' < key && key <= '9') {
		ut8 ch = key;
		r_core_visual_jump (core, ch);
		cur->model->addr = core->offset;
		cur->view->refresh = true;
		goto repeat;
	}

	const char *cmd;
	RConsCanvas *can = panels->can;
	switch (key) {
	case 'u':
		undoSeek (core);
		break;
	case 'U':
		redoSeek (core);
		break;
	case 'p':
		rotatePanels (panels, false);
		break;
	case 'P':
		rotatePanels (panels, true);
		break;
	case '.':
		if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
					strcmp (cur->model->cmd, "pdc")) {
			ut64 addr = r_debug_reg_get (core->dbg, "PC");
			if (addr && addr != UT64_MAX) {
				r_core_seek (core, addr, 1);
			} else {
				addr = r_num_get (core->num, "entry0");
				if (addr && addr != UT64_MAX) {
					r_core_seek (core, addr, 1);
				}
			}
			cur->model->addr = core->offset;
			cur->view->refresh = true;
		}
		break;
	case '?':
		toggleHelp (core);
		break;
	case 'b':
		r_core_visual_browse (core, NULL);
		break;
	case ';':
		handleComment (core);
		break;
	case 's':
		panelSingleStepIn (core);
		if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
					strcmp (cur->model->cmd, "pdc")) {
			cur->model->addr = core->offset;
		}
		setRefreshAll (panels, false);
		break;
	case 'S':
		panelSingleStepOver (core);
		if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
					strcmp (cur->model->cmd, "pdc")) {
			cur->model->addr = core->offset;
		}
		setRefreshAll (panels, false);
		break;
	case ' ':
		if (r_config_get_i (core->config, "graph.web")) {
			r_core_cmd0 (core, "agv $$");
		} else {
			callVisualGraph (core);
		}
		break;
	case ':':
		r_core_visual_prompt_input (core);
		cur->model->addr = core->offset;
		setRefreshAll (panels, false);
		break;
	case 'c':
		activateCursor (core);
		break;
	case 'C':
		{
			int color = r_config_get_i (core->config, "scr.color");
			if (++color > 2) {
				color = 0;
			}
			r_config_set_i (core->config, "scr.color", color);
			can->color = color;
			setRefreshAll (panels, true);
		}
		break;
	case 'r':
		if (r_config_get_i (core->config, "asm.hint.call")) {
			r_core_cmd0 (core, "e!asm.hint.call");
			r_core_cmd0 (core, "e!asm.hint.jmp");
		} else if (r_config_get_i (core->config, "asm.hint.jmp")) {
			r_core_cmd0 (core, "e!asm.hint.jmp");
			r_core_cmd0 (core, "e!asm.hint.lea");
		} else if (r_config_get_i (core->config, "asm.hint.lea")) {
			r_core_cmd0 (core, "e!asm.hint.lea");
			r_core_cmd0 (core, "e!asm.hint.call");
		}
		setRefreshAll (panels, false);
		break;
	case 'R':
		if (r_config_get_i (core->config, "scr.randpal")) {
			r_core_cmd0 (core, "ecr");
		} else {
			r_core_cmd0 (core, "ecn");
		}
		doPanelsRefresh (core);
		break;
	case 'a':
		panels->autoUpdate = r_cons_yesno ('y', "Auto update On? (Y/n)");
		break;
	case 'A':
		r_core_visual_asm (core, core->offset);
		break;
	case 'd':
		r_core_visual_define (core, "", 0);
		setRefreshAll (panels, false);
		break;
	case 'D':
		replaceCmd (core, PANEL_TITLE_DISASSEMBLY, PANEL_CMD_DISASSEMBLY, 0);
		break;
	case 'j':
		r_cons_switchbuf (false);
		if (cur->model->directionCb) {
			cur->model->directionCb (core, (int)DOWN);
		}
		break;
	case 'k':
		r_cons_switchbuf (false);
		if (cur->model->directionCb) {
			cur->model->directionCb (core, (int)UP);
		}
		break;
	case 'K':
		r_cons_switchbuf (false);
		if (cur->model->directionCb) {
			for (i = 0; i < getCurPanel (panels)->view->pos.h / 2 - 6; i++) {
				cur->model->directionCb (core, (int)UP);
			}
		}
		break;
	case 'J':
		r_cons_switchbuf (false);
		if (cur->model->directionCb) {
			for (i = 0; i < getCurPanel (panels)->view->pos.h / 2 - 6; i++) {
				cur->model->directionCb (core, (int)DOWN);
			}
		}
		break;
	case 'H':
		r_cons_switchbuf (false);
		if (cur->model->directionCb) {
			for (i = 0; i < getCurPanel (panels)->view->pos.w / 3; i++) {
				cur->model->directionCb (core, (int)LEFT);
			}
		}
		break;
	case 'L':
		r_cons_switchbuf (false);
		if (cur->model->directionCb) {
			for (i = 0; i < getCurPanel (panels)->view->pos.w / 3; i++) {
				cur->model->directionCb (core, (int)RIGHT);
			}
		}
		break;
	case 'f':
		set_filter (cur);
		break;
	case 'F':
		reset_filter (cur);
		break;
	case '_':
		hudstuff (core);
		break;
	case '\\':
		r_core_visual_hud (core);
		break;
	case 'n':
		if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
				strcmp (cur->model->cmd, "pdc")) {
			r_core_seek_next (core, r_config_get (core->config, "scr.nkey"));
			cur->model->addr = core->offset;
			cur->view->refresh = true;
		}
		break;
	case 'N':
		if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
				strcmp (cur->model->cmd, "pdc")) {
			r_core_seek_previous (core, r_config_get (core->config, "scr.nkey"));
			cur->model->addr = core->offset;
			cur->view->refresh = true;
		}
		break;
	case 'x':
		r_core_visual_refs (core, true, true);
		cur->model->addr = core->offset;
		setRefreshAll (panels, false);
		break;
	case 'X':
		r_core_visual_refs (core, false, true);
		cur->model->addr = core->offset;
		setRefreshAll (panels, false);
		break;
	case 9: // TAB
		handleTabKey (core, false);
		break;
	case 'Z': // SHIFT-TAB
		handleTabKey (core, true);
		break;
	case 'M':
	{
		if (!checkPanelNum (panels)) {
			break;
		}
		char *name = r_cons_input ("Name: ");
		char *cmd = r_cons_input ("Command: ");
		bool cache = r_cons_yesno ('y', "Cache the result? (Y/n)");
		if (name && *name && cmd && *cmd) {
			addNewPanel (core, name, cmd, cache);
		}
		free (name);
		free (cmd);
	}
	break;
	case 'e':
	{
		char *new_name = r_cons_input ("New name: ");
		char *new_cmd = r_cons_input ("New command: ");
		bool cache = r_cons_yesno ('y', "Cache the result? (Y/n)");
		if (new_name && *new_name && new_cmd && *new_cmd) {
			replaceCmd (core, new_name, new_cmd, cache);
		}
		free (new_name);
		free (new_cmd);
	}
		break;
	case 'm':
		setMode (panels, PANEL_MODE_MENU);
		clearPanelsMenu (core);
		getCurPanel (panels)->view->refresh = true;
		break;
	case 'g':
		r_core_visual_showcursor (core, true);
		r_core_visual_offset (core);
		r_core_visual_showcursor (core, false);
		cur->model->addr = core->offset;
		cur->view->refresh = true;
		break;
	case 'G':
		if (checkFunc (core)) {
			replaceCmd (core, PANEL_TITLE_GRAPH, PANEL_CMD_GRAPH, 1);
		}
		break;
	case 'h':
		r_cons_switchbuf (false);
		if (cur->model->directionCb) {
			cur->model->directionCb (core, (int)LEFT);
		}
		break;
	case 'l':
		r_cons_switchbuf (false);
		if (cur->model->directionCb) {
			cur->model->directionCb (core, (int)RIGHT);
		}
		break;
	case 'V':
		if (r_config_get_i (core->config, "graph.web")) {
			r_core_cmd0 (core, "agv $$");
		} else {
			callVisualGraph (core);
		}
		break;
	case ']':
		r_config_set_i (core->config, "hex.cols", r_config_get_i (core->config, "hex.cols") + 1);
		break;
	case '[':
		r_config_set_i (core->config, "hex.cols", r_config_get_i (core->config, "hex.cols") - 1);
		break;
	case '/':
		r_core_cmd0 (core, "?i highlight;e scr.highlight=`yp`");
		break;
	case 'z':
		if (panels->curnode > 0) {
			swapPanels (panels, 0, panels->curnode);
			panels->curnode = 0;
			setRefreshAll (panels, false);
		}
		break;
	case 'i':
		if (cur->model->rotateCb) {
			cur->model->rotateCb (core, false);
			cur->view->refresh = true;
		}
		break;
	case 'I':
		if (cur->model->rotateCb) {
			cur->model->rotateCb (core, true);
			cur->view->refresh = true;
		}
		break;
	case 't':
		if (handle_tab (core)) {
			return false;
		}
		break;
	case 'T':
		if (panels_root->n_panels > 1) {
			goto exit;
		}
		break;
	case 'w':
		toggleWindowMode (panels);
		setRefreshAll (panels, false);
		break;
	case 0x0d: // "\\n"
		toggleZoomMode (panels);
		break;
	case '|':
		{
			RPanel *p = getCurPanel (panels);
			splitPanelVertical (core, p, p->model->title, p->model->cmd, p->model->cache);
			break;
		}
	case '-':
		{
			RPanel *p = getCurPanel (panels);
			splitPanelHorizontal (core, p, p->model->title, p->model->cmd, p->model->cache);
			break;
		}
	case '*':
		if (checkFunc (core)) {
			r_cons_canvas_free (can);
			panels->can = NULL;

			replaceCmd (core, PANEL_TITLE_DECOMPILER, "pdc", 1);

			int h, w = r_cons_get_size (&h);
			panels->can = createNewCanvas (core, w, h);
		}
		break;
	case '(':
		if (panels->fun != PANEL_FUN_SNOW && panels->fun != PANEL_FUN_SAKURA) {
			//TODO: Refactoring the FUN if bored af
			//panels->fun = PANEL_FUN_SNOW;
			panels->fun = PANEL_FUN_SAKURA;
		} else {
			panels->fun = PANEL_FUN_NOFUN;
			resetSnow (panels);
		}
		break;
	case ')':
		rotateAsmemu (core, getCurPanel (panels));
		break;
	case '&':
		toggleCache (getCurPanel (panels));
		resetScrollPos (getCurPanel (panels));
		break;
	case R_CONS_KEY_F1:
		cmd = r_config_get (core->config, "key.f1");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		}
		break;
	case R_CONS_KEY_F2:
		cmd = r_config_get (core->config, "key.f2");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		} else {
			panelBreakpoint (core);
		}
		break;
	case R_CONS_KEY_F3:
		cmd = r_config_get (core->config, "key.f3");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		}
		break;
	case R_CONS_KEY_F4:
		cmd = r_config_get (core->config, "key.f4");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		}
		break;
	case R_CONS_KEY_F5:
		cmd = r_config_get (core->config, "key.f5");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		}
		break;
	case R_CONS_KEY_F6:
		cmd = r_config_get (core->config, "key.f6");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		}
		break;
	case R_CONS_KEY_F7:
		cmd = r_config_get (core->config, "key.f7");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		} else {
			panelSingleStepIn (core);
			setRefreshAll (panels, false);
		}
		break;
	case R_CONS_KEY_F8:
		cmd = r_config_get (core->config, "key.f8");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		} else {
			panelSingleStepOver (core);
			setRefreshAll (panels, false);
		}
		break;
	case R_CONS_KEY_F9:
		cmd = r_config_get (core->config, "key.f9");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		} else {
			panelContinue (core);
		}
		break;
	case R_CONS_KEY_F10:
		cmd = r_config_get (core->config, "key.f10");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		}
		break;
	case R_CONS_KEY_F11:
		cmd = r_config_get (core->config, "key.f11");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		}
		break;
	case R_CONS_KEY_F12:
		cmd = r_config_get (core->config, "key.f12");
		if (cmd && *cmd) {
			(void)r_core_cmd0 (core, cmd);
		}
		break;
	case 'Q':
		*force_quit = true;
		goto exit;
	case '!':
	case 'q':
	case -1: // EOF
		goto exit;
#if 0
	case 27: // ESC
		if (r_cons_readchar () == 91) {
			if (r_cons_readchar () == 90) {}
		}
		break;
#endif
	default:
		// eprintf ("Key %d\n", key);
		// sleep (1);
		break;
	}
	goto repeat;
exit:
	core->cons->event_resize = NULL;
	core->cons->event_data = NULL;
	core->print->cur = originCursor;
	core->print->cur_enabled = false;
	core->print->col = 0;
	core->vmode = originVmode;
	core->panels = prev;
	return true;
}
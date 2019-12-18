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
struct TYPE_5__ {TYPE_1__* model; } ;
struct TYPE_4__ {char* cmd; } ;
typedef  TYPE_2__ RPanel ;

/* Variables and functions */
 int COUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PANEL_CMD_DECOMPILER ; 
 int /*<<< orphan*/  PANEL_CMD_DECOMPILER_O ; 
 int /*<<< orphan*/  PANEL_CMD_DISASMSUMMARY ; 
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_CMD_HEXDUMP ; 
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 scalar_t__ R_STR_ISEMPTY (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * hexdump_rotate ; 
 char* r_str_new (char*) ; 
 int r_str_split (char*,char) ; 
 char* r_str_word_get0 (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

bool __check_panel_type(RPanel *panel, const char *type) {
	if (!panel->model->cmd || !type) {
		return false;
	}
	char *tmp = r_str_new (panel->model->cmd);
	int n = r_str_split (tmp, ' ');
	if (!n) {
		free (tmp);
		return false;
	}
	const char *base = r_str_word_get0 (tmp, 0);
	if (R_STR_ISEMPTY (base)) {
		free (tmp);
		return false;
	}
	int len = strlen (type);
	if (!strcmp (type, PANEL_CMD_DISASSEMBLY)) {
		if (!strncmp (tmp, type, len) &&
				strcmp (panel->model->cmd, PANEL_CMD_DECOMPILER) &&
				strcmp (panel->model->cmd, PANEL_CMD_DECOMPILER_O) &&
				strcmp (panel->model->cmd, PANEL_CMD_DISASMSUMMARY)) {
			free (tmp);
			return true;
		}
		free (tmp);
		return false;
	}
	if (!strcmp (type, PANEL_CMD_STACK)) {
		if (!strcmp (tmp, PANEL_CMD_STACK)) {
			free (tmp);
			return true;
		}
		free (tmp);
		return false;
	}
	if (!strcmp (type, PANEL_CMD_HEXDUMP)) {
		int i = 0;
		for (; i < COUNT (hexdump_rotate); i++) {
			if (!strcmp (tmp, hexdump_rotate[i])) {
				free (tmp);
				return true;
			}
		}
		free (tmp);
		return false;
	}
	free (tmp);
	return !strncmp (panel->model->cmd, type, len);
}
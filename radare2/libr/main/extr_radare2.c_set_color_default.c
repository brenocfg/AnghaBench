#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_MODE_16 ; 
 int /*<<< orphan*/  COLOR_MODE_16M ; 
 int /*<<< orphan*/  COLOR_MODE_256 ; 
 int /*<<< orphan*/  COLOR_MODE_DISABLED ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ r ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ r_str_endswith (char*,char*) ; 
 char* r_sys_getenv (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void set_color_default(void) {
#ifdef __WINDOWS__
	char *alacritty = r_sys_getenv ("ALACRITTY_LOG");
	if (alacritty) {
		// Despite the setting of env vars to the contrary, Alacritty on
		// Windows may not actually support >16 colors out-of-the-box
		// (https://github.com/jwilm/alacritty/issues/1662).
		// TODO: Windows 10 version check.
		r_config_set_i (r.config, "scr.color", COLOR_MODE_16);
		free (alacritty);
		return;
	}
#endif
	char *tmp = r_sys_getenv ("COLORTERM");
	if (tmp) {
		if ((r_str_endswith (tmp, "truecolor") || r_str_endswith (tmp, "24bit"))) {
			r_config_set_i (r.config, "scr.color", COLOR_MODE_16M);
		}
	} else {
		tmp = r_sys_getenv ("TERM");
		if (!tmp) {
			return;
		}
		if (r_str_endswith (tmp, "truecolor") || r_str_endswith (tmp, "24bit")) {
			r_config_set_i (r.config, "scr.color", COLOR_MODE_16M);
		} else if (r_str_endswith (tmp, "256color")) {
			r_config_set_i (r.config, "scr.color", COLOR_MODE_256);
		} else if (!strcmp (tmp, "dumb")) {
			// Dumb terminals don't get color by default.
			r_config_set_i (r.config, "scr.color", COLOR_MODE_DISABLED);
		}
	}
	free (tmp);
}
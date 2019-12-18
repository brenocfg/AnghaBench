#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __add_menu (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __config_toggle_cb ; 
 int /*<<< orphan*/  __config_value_cb ; 
 char** menus_settings_screen ; 
 char* r_config_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void __init_menu_screen_settings_layout(void *_core, const char *parent) {
	RCore *core = (RCore *)_core;
	RStrBuf *rsb = r_strbuf_new (NULL);
	int i = 0;
	while (menus_settings_screen[i]) {
		const char *menu = menus_settings_screen[i];
		r_strbuf_set (rsb, menu);
		r_strbuf_append (rsb, ": ");
		r_strbuf_append (rsb, r_config_get (core->config, menu));
		if (!strcmp (menus_settings_screen[i], "scr.color")) {
			__add_menu (core, parent, r_strbuf_get (rsb), __config_value_cb);
		} else {
			__add_menu (core, parent, r_strbuf_get (rsb), __config_toggle_cb);
		}
		i++;
	}
	r_strbuf_free (rsb);
}
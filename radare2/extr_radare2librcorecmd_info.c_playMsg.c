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
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 char* r_str_newf (char*,...) ; 
 int /*<<< orphan*/  r_sys_tts (char*,int) ; 

__attribute__((used)) static void playMsg(RCore *core, const char *n, int len) {
	if (r_config_get_i (core->config, "scr.tts")) {
		if (len > 0) {
			char *s = r_str_newf ("%d %s", len, n);
			r_sys_tts (s, true);
			free (s);
		} else if (len == 0) {
			char *s = r_str_newf ("there are no %s", n);
			r_sys_tts (s, true);
			free (s);
		}
	}
}
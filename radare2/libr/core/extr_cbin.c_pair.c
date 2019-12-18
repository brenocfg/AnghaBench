#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ IS_MODE_JSON (int) ; 
 int const PAIR_WIDTH ; 
 int /*<<< orphan*/  memset (char*,char,int const) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char const*,char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void pair(const char *key, const char *val, int mode, bool last) {
	if (!val || !*val) {
		return;
	}
	if (IS_MODE_JSON (mode)) {
		const char *lst = last ? "" : ",";
		r_cons_printf ("\"%s\":%s%s", key, val, lst);
	} else {
		char ws[16];
		const int keyl = strlen (key);
		const int wl = (keyl > PAIR_WIDTH) ? 0 : PAIR_WIDTH - keyl;
		memset (ws, ' ', wl);
		ws[wl] = 0;
		r_cons_printf ("%s%s%s\n", key, ws, val);
	}
}
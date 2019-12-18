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
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_fgets (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_set_raw (int) ; 
 int /*<<< orphan*/  r_cons_show_cursor (int) ; 
 int /*<<< orphan*/  r_line_set_prompt (char const*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *__prompt(const char *msg, void *p) {
	char res[128];
	r_cons_show_cursor (true);
	r_cons_set_raw (false);
	r_line_set_prompt (msg);
	res[0] =0;
	if (!r_cons_fgets (res, sizeof (res), 0, NULL)) {
		res[0] = 0;
	}
	return strdup (res);
}
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
 int /*<<< orphan*/  r_cons_fgets (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_core_visual_showcursor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_line_set_prompt (char const*) ; 

__attribute__((used)) static void prompt_read(const char *p, char *buf, int buflen) {
	if (!buf || buflen < 1) {
		return;
	}
	*buf = 0;
	r_line_set_prompt (p);
	r_core_visual_showcursor (NULL, true);
	r_cons_fgets (buf, buflen, 0, NULL);
	r_core_visual_showcursor (NULL, false);
}
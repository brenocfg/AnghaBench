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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* get_graph_commands (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ r_cons_is_breaked () ; 
 int /*<<< orphan*/  r_core_cmd0 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_return_if_fail (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 

__attribute__((used)) static void __generate_graph (RCore *c, ut64 off) {
        r_return_if_fail (c);
        char *ptr = get_graph_commands (c, off);
	char *str = ptr;
        r_cons_break_push (NULL, NULL);
        if (str) {
                for (;;) {
                        if (r_cons_is_breaked ()) {
                                break;
                        }
                        char *eol = strchr (ptr, '\n');
                        if (eol) {
                                *eol = '\0';
                        }
                        if (*ptr) {
                                char *p = strdup (ptr);
                                if (!p) {
                                        free (str);
                                        return;
                                }
                                r_core_cmd0 (c, p);
                                free (p);
                        }
                        if (!eol) {
                                break;
                        }
                        ptr = eol + 1;
                }
		free (str);
        }
        r_cons_break_pop ();
}
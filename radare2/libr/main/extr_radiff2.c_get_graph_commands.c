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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_2__ {int is_html; } ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int R_CORE_ANAL_GRAPHBODY ; 
 int R_CORE_ANAL_GRAPHDIFF ; 
 int R_CORE_ANAL_STAR ; 
 int /*<<< orphan*/  r_cons_echo (int /*<<< orphan*/ *) ; 
 char* r_cons_get_buffer () ; 
 int /*<<< orphan*/  r_cons_pop () ; 
 int /*<<< orphan*/  r_cons_push () ; 
 TYPE_1__* r_cons_singleton () ; 
 int /*<<< orphan*/  r_core_anal_graph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *get_graph_commands(RCore *c, ut64 off) {
        bool tmp_html = r_cons_singleton ()->is_html;
        r_cons_singleton ()->is_html = false;
        r_cons_push ();
        r_core_anal_graph (c, off, R_CORE_ANAL_GRAPHBODY | R_CORE_ANAL_GRAPHDIFF |  R_CORE_ANAL_STAR);
        const char *static_str = r_cons_get_buffer ();
        char *retstr = strdup (static_str? static_str: "");
        r_cons_pop ();
        r_cons_echo (NULL);
        r_cons_singleton ()->is_html = tmp_html;
        return retstr;
}
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
struct pid_stat {int /*<<< orphan*/  stat_collected_usec; scalar_t__ updated; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_log (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  debug_print_process_and_parents (struct pid_stat*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void debug_print_process_tree(struct pid_stat *p, char *msg) {
    debug_log("%s: process %s (%d, %s) with parents:", msg, p->comm, p->pid, p->updated?"running":"exited");
    debug_print_process_and_parents(p, p->stat_collected_usec);
}
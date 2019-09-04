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
struct tep_handle {struct cmdline_list* cmdlist; } ;
struct cmdline_list {struct cmdline_list* next; int /*<<< orphan*/  comm; } ;
struct cmdline {int dummy; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct cmdline *
pid_from_cmdlist(struct tep_handle *pevent, const char *comm, struct cmdline *next)
{
	struct cmdline_list *cmdlist = (struct cmdline_list *)next;

	if (cmdlist)
		cmdlist = cmdlist->next;
	else
		cmdlist = pevent->cmdlist;

	while (cmdlist && strcmp(cmdlist->comm, comm) != 0)
		cmdlist = cmdlist->next;

	return (struct cmdline *)cmdlist;
}
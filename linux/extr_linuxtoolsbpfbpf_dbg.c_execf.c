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
struct TYPE_3__ {char* name; int (* func ) (char*) ;} ;

/* Variables and functions */
 int array_size (TYPE_1__*) ; 
 TYPE_1__* cmds ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strtok_r (char*,char*,char**) ; 
 int stub1 (char*) ; 

__attribute__((used)) static int execf(char *arg)
{
	char *cmd, *cont, *tmp = strdup(arg);
	int i, ret = 0, len;

	cmd = strtok_r(tmp, " ", &cont);
	if (cmd == NULL)
		goto out;
	len = strlen(cmd);
	for (i = 0; i < array_size(cmds); i++) {
		if (len != strlen(cmds[i].name))
			continue;
		if (strncmp(cmds[i].name, cmd, len) == 0) {
			ret = cmds[i].func(cont);
			break;
		}
	}
out:
	free(tmp);
	return ret;
}
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
typedef  int /*<<< orphan*/  MetaCommand ;

/* Variables and functions */
 int /*<<< orphan*/  META_ELIF ; 
 int /*<<< orphan*/  META_ELSE ; 
 int /*<<< orphan*/  META_ENDIF ; 
 int /*<<< orphan*/  META_GSET ; 
 int /*<<< orphan*/  META_IF ; 
 int /*<<< orphan*/  META_NONE ; 
 int /*<<< orphan*/  META_SET ; 
 int /*<<< orphan*/  META_SETSHELL ; 
 int /*<<< orphan*/  META_SHELL ; 
 int /*<<< orphan*/  META_SLEEP ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 

__attribute__((used)) static MetaCommand
getMetaCommand(const char *cmd)
{
	MetaCommand mc;

	if (cmd == NULL)
		mc = META_NONE;
	else if (pg_strcasecmp(cmd, "set") == 0)
		mc = META_SET;
	else if (pg_strcasecmp(cmd, "setshell") == 0)
		mc = META_SETSHELL;
	else if (pg_strcasecmp(cmd, "shell") == 0)
		mc = META_SHELL;
	else if (pg_strcasecmp(cmd, "sleep") == 0)
		mc = META_SLEEP;
	else if (pg_strcasecmp(cmd, "if") == 0)
		mc = META_IF;
	else if (pg_strcasecmp(cmd, "elif") == 0)
		mc = META_ELIF;
	else if (pg_strcasecmp(cmd, "else") == 0)
		mc = META_ELSE;
	else if (pg_strcasecmp(cmd, "endif") == 0)
		mc = META_ENDIF;
	else if (pg_strcasecmp(cmd, "gset") == 0)
		mc = META_GSET;
	else
		mc = META_NONE;
	return mc;
}
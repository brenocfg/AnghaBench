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
struct command {int (* fn ) (int,char**) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int stub1 (int,char**) ; 

__attribute__((used)) static int run_command(const struct command *cmd, int argc, char *argv[])
{
	dbg("running command: `%s'", cmd->name);
	return cmd->fn(argc, argv);
}
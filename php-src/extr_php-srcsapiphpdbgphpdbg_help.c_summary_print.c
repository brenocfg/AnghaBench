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
struct TYPE_3__ {int /*<<< orphan*/  tip; int /*<<< orphan*/  alias; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ phpdbg_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  pretty_print (char*) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void summary_print(phpdbg_command_t const * const cmd)
{
	char *summary;
	spprintf(&summary, 0, "Command: **%s**  Alias: **%c**  **%s**\n", cmd->name, cmd->alias, cmd->tip);
	pretty_print(summary);
	efree(summary);
}
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
struct TYPE_3__ {int argc; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ Command ;
typedef  int /*<<< orphan*/  CState ;

/* Variables and functions */
 char* getVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getQueryParams(CState *st, const Command *command, const char **params)
{
	int			i;

	for (i = 0; i < command->argc - 1; i++)
		params[i] = getVariable(st, command->argv[i + 1]);
}
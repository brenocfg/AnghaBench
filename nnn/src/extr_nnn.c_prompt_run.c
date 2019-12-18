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
 int F_CLI ; 
 int F_CONFIRM ; 
 size_t NCUR ; 
 int /*<<< orphan*/ * envs ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  shell ; 
 int /*<<< orphan*/  spawn (int /*<<< orphan*/ ,char*,char*,char const*,int) ; 

__attribute__((used)) static void prompt_run(char *cmd, const char *cur, const char *path)
{
	setenv(envs[NCUR], cur, 1);
	spawn(shell, "-c", cmd, path, F_CLI | F_CONFIRM);
}
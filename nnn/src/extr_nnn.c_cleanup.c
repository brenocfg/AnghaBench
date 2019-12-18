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
 int /*<<< orphan*/  bmstr ; 
 int /*<<< orphan*/  cfgdir ; 
 int /*<<< orphan*/  disabledbg () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_pipepath ; 
 int /*<<< orphan*/  g_selpath ; 
 int /*<<< orphan*/  initpath ; 
 int /*<<< orphan*/  plugindir ; 
 int /*<<< orphan*/  pluginstr ; 
 int /*<<< orphan*/  sessiondir ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup(void)
{
	free(g_selpath);
	free(plugindir);
	free(sessiondir);
	free(cfgdir);
	free(initpath);
	free(bmstr);
	free(pluginstr);

	unlink(g_pipepath);

#ifdef DBGMODE
	disabledbg();
#endif
}
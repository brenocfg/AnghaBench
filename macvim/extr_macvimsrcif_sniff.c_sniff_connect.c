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
 scalar_t__ ConnectToSniffEmacs () ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__* init_cmds ; 
 scalar_t__ sniff_connected ; 
 int /*<<< orphan*/  vi_error_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_exec_cmd (scalar_t__) ; 

__attribute__((used)) static void
sniff_connect()
{
    if (sniff_connected)
	return;
    if (ConnectToSniffEmacs())
	vi_error_msg(_("E276: Error connecting to SNiFF+"));
    else
    {
	int i;

	for (i = 0; init_cmds[i]; i++)
	    vi_exec_cmd(init_cmds[i]);
    }
}
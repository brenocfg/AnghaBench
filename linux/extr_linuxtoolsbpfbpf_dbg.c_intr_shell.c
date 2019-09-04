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
 int /*<<< orphan*/  rl_crlf () ; 
 scalar_t__ rl_end ; 
 int /*<<< orphan*/  rl_free_line_state () ; 
 int /*<<< orphan*/  rl_kill_line (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_refresh_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intr_shell(int sig)
{
	if (rl_end)
		rl_kill_line(-1, 0);

	rl_crlf();
	rl_refresh_line(0, 0);
	rl_free_line_state();
}
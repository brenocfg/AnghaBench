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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execl (char const*,char const*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exec_other_validate_cap(const char *name,
				    bool eff, bool perm, bool inh, bool ambient)
{
	execl(name, name, (eff ? "1" : "0"),
	      (perm ? "1" : "0"), (inh ? "1" : "0"), (ambient ? "1" : "0"),
	      NULL);
	ksft_exit_fail_msg("execl - %s\n", strerror(errno));
}
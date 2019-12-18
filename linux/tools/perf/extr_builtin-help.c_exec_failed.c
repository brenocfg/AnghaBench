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
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int STRERR_BUFSIZE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pr_warning (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_error_r (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void exec_failed(const char *cmd)
{
	char sbuf[STRERR_BUFSIZE];
	pr_warning("failed to exec '%s': %s", cmd, str_error_r(errno, sbuf, sizeof(sbuf)));
}
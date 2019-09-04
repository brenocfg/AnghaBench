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
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  str_error_r (int,char*,int) ; 

__attribute__((used)) static void pr_err_with_code(const char *msg, int err)
{
	char sbuf[STRERR_BUFSIZE];

	pr_err("%s", msg);
	pr_debug(" Reason: %s (Code: %d)",
		 str_error_r(-err, sbuf, sizeof(sbuf)), err);
	pr_err("\n");
}
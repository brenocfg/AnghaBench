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
 int SBC7240_MAX_TIMEOUT ; 
 int /*<<< orphan*/  SBC7240_SET_TIMEOUT_PORT ; 
 int /*<<< orphan*/  outb_p (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int timeout ; 

__attribute__((used)) static int wdt_set_timeout(int t)
{
	if (t < 1 || t > SBC7240_MAX_TIMEOUT) {
		pr_err("timeout value must be 1<=x<=%d\n", SBC7240_MAX_TIMEOUT);
		return -1;
	}
	/* set the timeout */
	outb_p((unsigned)t, SBC7240_SET_TIMEOUT_PORT);
	timeout = t;
	pr_info("timeout set to %d seconds\n", t);
	return 0;
}
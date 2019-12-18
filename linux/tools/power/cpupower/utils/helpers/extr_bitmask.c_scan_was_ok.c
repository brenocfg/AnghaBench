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
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static int scan_was_ok(int sret, char nextc, const char *ok_next_chars)
{
	return sret == 1 ||
		(sret == 2 && strchr(ok_next_chars, nextc) != NULL);
}
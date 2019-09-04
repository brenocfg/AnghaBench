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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int utilfdt_read_err_len (char const*,char**,int /*<<< orphan*/ *) ; 

int utilfdt_read_err(const char *filename, char **buffp)
{
	off_t len;
	return utilfdt_read_err_len(filename, buffp, &len);
}
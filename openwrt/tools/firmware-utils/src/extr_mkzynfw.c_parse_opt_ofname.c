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
 int /*<<< orphan*/  ERR (char*) ; 
 char* ofname ; 
 scalar_t__ required_arg (char,char*) ; 

int
parse_opt_ofname(char ch, char *arg)
{

	if (ofname != NULL) {
		ERR("only one output file allowed");
		return -1;
	}

	if (required_arg(ch, arg))
		return -1;

	ofname = arg;

	return 0;
}
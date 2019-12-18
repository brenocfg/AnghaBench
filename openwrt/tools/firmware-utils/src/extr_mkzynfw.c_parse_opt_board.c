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
 int /*<<< orphan*/  DBG (int,char*,char,char*) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/ * board ; 
 int /*<<< orphan*/ * find_board (char*) ; 
 scalar_t__ required_arg (char,char*) ; 

int
parse_opt_board(char ch, char *arg)
{

	DBG(1,"parsing board option: -%c %s", ch, arg);

	if (board != NULL) {
		ERR("only one board option allowed");
		return -1;
	}

	if (required_arg(ch, arg))
		return -1;

	board = find_board(arg);
	if (board == NULL){
		ERR("invalid/unknown board specified: %s", arg);
		return -1;
	}

	return 0;
}
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
typedef  int /*<<< orphan*/  Rangstr ;

/* Variables and functions */
 int /*<<< orphan*/  json_path_first (int /*<<< orphan*/ *) ; 
 scalar_t__ json_path_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rangstr_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rangstr_new (char*) ; 
 int /*<<< orphan*/  rangstr_print (int /*<<< orphan*/ *) ; 

int test_parse_json_path() {
	Rangstr rs = rangstr_new ("ping.board[\"pop\"][1][2][\"caca\"].panda");
	json_path_first (&rs);
	do {
		printf (" - ");
		rangstr_print (&rs);
		printf (" Int (%d)", rangstr_int (&rs));
		printf ("\n");
	} while (json_path_next (&rs));
	printf ("--\n");
}
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
 int /*<<< orphan*/  DOING_SS ; 
 int KDB_ARGCOUNT ; 
 int KDB_CMD_SS ; 
 int /*<<< orphan*/  KDB_STATE_SET (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdb_ss(int argc, const char **argv)
{
	if (argc != 0)
		return KDB_ARGCOUNT;
	/*
	 * Set trace flag and go.
	 */
	KDB_STATE_SET(DOING_SS);
	return KDB_CMD_SS;
}
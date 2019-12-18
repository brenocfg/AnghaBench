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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* maccalc_name ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(void)
{
	fprintf(stderr,
		"Usage: %s <command>\n"
		"valid commands:\n"
		"  add <mac> <number>\n"
		"  and|or|xor <mac1> <mac2>\n"
		"  mac2bin <mac>\n"
		"  bin2mac\n",
		maccalc_name);
}
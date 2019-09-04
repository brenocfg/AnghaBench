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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int run_shell_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv)
{
	FILE *fin = NULL, *fout = NULL;

	if (argc >= 2)
		fin = fopen(argv[1], "r");
	if (argc >= 3)
		fout = fopen(argv[2], "w");

	return run_shell_loop(fin ? : stdin, fout ? : stdout);
}
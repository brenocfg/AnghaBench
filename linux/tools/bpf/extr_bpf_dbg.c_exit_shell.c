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
typedef  int /*<<< orphan*/  file ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  clear_history () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  rl_deprep_terminal () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  try_close_pcap () ; 
 int /*<<< orphan*/  write_history (char*) ; 

__attribute__((used)) static void exit_shell(FILE *fin, FILE *fout)
{
	char file[128];

	snprintf(file, sizeof(file), "%s/.bpf_dbg_history", getenv("HOME"));
	write_history(file);

	clear_history();
	rl_deprep_terminal();

	try_close_pcap();

	if (fin != stdin)
		fclose(fin);
	if (fout != stdout)
		fclose(fout);
}
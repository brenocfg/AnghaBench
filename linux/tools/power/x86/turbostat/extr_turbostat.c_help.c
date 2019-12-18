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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  outf ; 

void help(void)
{
	fprintf(outf,
	"Usage: turbostat [OPTIONS][(--interval seconds) | COMMAND ...]\n"
	"\n"
	"Turbostat forks the specified COMMAND and prints statistics\n"
	"when COMMAND completes.\n"
	"If no COMMAND is specified, turbostat wakes every 5-seconds\n"
	"to print statistics, until interrupted.\n"
	"  -a, --add	add a counter\n"
	"		  eg. --add msr0x10,u64,cpu,delta,MY_TSC\n"
	"  -c, --cpu	cpu-set	limit output to summary plus cpu-set:\n"
	"		  {core | package | j,k,l..m,n-p }\n"
	"  -d, --debug	displays usec, Time_Of_Day_Seconds and more debugging\n"
	"  -D, --Dump	displays the raw counter values\n"
	"  -e, --enable	[all | column]\n"
	"		shows all or the specified disabled column\n"
	"  -H, --hide [column|column,column,...]\n"
	"		hide the specified column(s)\n"
	"  -i, --interval sec.subsec\n"
	"		Override default 5-second measurement interval\n"
	"  -J, --Joules	displays energy in Joules instead of Watts\n"
	"  -l, --list	list column headers only\n"
	"  -n, --num_iterations num\n"
	"		number of the measurement iterations\n"
	"  -o, --out file\n"
	"		create or truncate \"file\" for all output\n"
	"  -q, --quiet	skip decoding system configuration header\n"
	"  -s, --show [column|column,column,...]\n"
	"		show only the specified column(s)\n"
	"  -S, --Summary\n"
	"		limits output to 1-line system summary per interval\n"
	"  -T, --TCC temperature\n"
	"		sets the Thermal Control Circuit temperature in\n"
	"		  degrees Celsius\n"
	"  -h, --help	print this help message\n"
	"  -v, --version	print version information\n"
	"\n"
	"For more help, run \"man turbostat\"\n");
}
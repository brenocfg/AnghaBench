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
 int blankcount ; 
 int blankmax ; 
 scalar_t__ compblank ; 
 int complement ; 
 scalar_t__ debugging ; 
 scalar_t__ delcount ; 
 int exitstat ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int linenum ; 
 scalar_t__ lnblank ; 
 scalar_t__ lnnum ; 
 char* newline ; 
 int /*<<< orphan*/  output ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 size_t strspn (char*,char*) ; 
 scalar_t__ symlist ; 
 char* tline ; 

__attribute__((used)) static void
flushline(bool keep)
{
	if (symlist)
		return;
	if (keep ^ complement) {
		bool blankline = tline[strspn(tline, " \t\r\n")] == '\0';
		if (blankline && compblank && blankcount != blankmax) {
			delcount += 1;
			blankcount += 1;
		} else {
			if (lnnum && delcount > 0)
				printf("#line %d%s", linenum, newline);
			fputs(tline, output);
			delcount = 0;
			blankmax = blankcount = blankline ? blankcount + 1 : 0;
		}
	} else {
		if (lnblank)
			fputs(newline, output);
		exitstat = 1;
		delcount += 1;
		blankcount = 0;
	}
	if (debugging)
		fflush(output);
}
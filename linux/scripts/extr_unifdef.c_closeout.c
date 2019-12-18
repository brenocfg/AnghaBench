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
 scalar_t__ EOF ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  ofilename ; 
 int /*<<< orphan*/  output ; 
 scalar_t__ overwriting ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ symdepth ; 
 int /*<<< orphan*/  tempname ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zerosyms ; 

__attribute__((used)) static void
closeout(void)
{
	if (symdepth && !zerosyms)
		printf("\n");
	if (fclose(output) == EOF) {
		warn("couldn't write to %s", ofilename);
		if (overwriting) {
			unlink(tempname);
			errx(2, "%s unchanged", filename);
		} else {
			exit(2);
		}
	}
}
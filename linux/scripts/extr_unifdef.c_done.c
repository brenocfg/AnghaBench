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
 int /*<<< orphan*/  closeout () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exitstat ; 
 scalar_t__ incomment ; 
 int /*<<< orphan*/  ofilename ; 
 scalar_t__ overwriting ; 
 int rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempname ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
done(void)
{
	if (incomment)
		error("EOF in comment");
	closeout();
	if (overwriting && rename(tempname, ofilename) == -1) {
		warn("couldn't rename temporary file");
		unlink(tempname);
		errx(2, "%s unchanged", ofilename);
	}
	exit(exitstat);
}
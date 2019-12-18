#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  picker; } ;

/* Variables and functions */
 TYPE_1__ cfg ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exitcurses () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ g_selpath ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pselbuf ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 
 int /*<<< orphan*/  xitoa (int) ; 

__attribute__((used)) static void printerr(int linenum)
{
	exitcurses();
	perror(xitoa(linenum));
	if (!cfg.picker && g_selpath)
		unlink(g_selpath);
	free(pselbuf);
	exit(1);
}
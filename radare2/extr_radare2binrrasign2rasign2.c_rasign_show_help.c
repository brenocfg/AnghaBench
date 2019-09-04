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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int rasign_show_help() {
	printf ("Usage: rasign2 [options] [file]\n"
	" -r            show output in radare commands\n"
	" -j            show output in json\n"
	" -s [sigfile]  specify one or more signature files\n"
	"Examples:\n"
	"  rasign2 libc.so.6 > libc.sig\n"
	"  rasign2 -s libc.sig ls.static\n");
	return 0;
}
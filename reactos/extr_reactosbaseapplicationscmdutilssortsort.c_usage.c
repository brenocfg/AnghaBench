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
 scalar_t__ err ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void usage(void)
{
    fputs("SORT\n", stderr);
    fputs("Sorts input and writes output to a file, console or a device.\n",
          stderr);

    if (err)
    {
        fputs("Invalid parameter\n", stderr);
    }

    fputs("    SORT [options] < [drive:1][path1]file1 > [drive2:][path2]file2\n",
          stderr);

    fputs("    Command | SORT [options] > [drive:][path]file\n", stderr);
    fputs("    Options:\n", stderr);
    fputs("    /R   Reverse order\n", stderr);
    fputs("    /+n  Start sorting with column n\n", stderr);
    fputs("    /?   Help\n", stderr);
}
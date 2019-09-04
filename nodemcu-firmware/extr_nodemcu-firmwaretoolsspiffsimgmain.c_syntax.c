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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void syntax (void)
{
  fprintf (stderr,
    "Syntax: spiffsimg -f <filename> [-d] [-o <locationfilename>] [-c size] [-S flashsize] [-U usedsize] [-l | -i | -r <scriptname> ]\n\n"
  );
  exit (1);
}
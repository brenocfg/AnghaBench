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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

extern int
s_rnge(char *var, int index, char *routine, int lineno)
{
    fprintf(stderr, "array index out-of-bounds for %s[%d] in routine %s:%d\n",
            var, index, routine, lineno);
    fflush(stderr);
    abort();
}
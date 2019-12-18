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
struct argv {char** argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_grow (struct argv*,int) ; 

__attribute__((used)) static void
argv_append(struct argv *a, char *str)  /* str must have been malloced or be NULL */
{
    argv_grow(a, 1);
    a->argv[a->argc++] = str;
}
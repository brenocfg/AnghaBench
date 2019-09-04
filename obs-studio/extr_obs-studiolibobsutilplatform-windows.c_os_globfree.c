#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t gl_pathc; struct TYPE_4__* gl_pathv; struct TYPE_4__* path; } ;
typedef  TYPE_1__ os_glob_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 

void os_globfree(os_glob_t *pglob)
{
	if (pglob) {
		for (size_t i = 0; i < pglob->gl_pathc; i++)
			bfree(pglob->gl_pathv[i].path);
		bfree(pglob->gl_pathv);
		bfree(pglob);
	}
}
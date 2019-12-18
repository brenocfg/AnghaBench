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
 scalar_t__ FAIL ; 
 int OK ; 
 scalar_t__ alloc_typebuf () ; 
 int /*<<< orphan*/  closescript () ; 
 size_t curscript ; 
 int /*<<< orphan*/  init_typebuf () ; 
 int /*<<< orphan*/ * saved_typebuf ; 
 int /*<<< orphan*/  typebuf ; 

int
save_typebuf()
{
    init_typebuf();
    saved_typebuf[curscript] = typebuf;
    /* If out of memory: restore typebuf and close file. */
    if (alloc_typebuf() == FAIL)
    {
	closescript();
	return FAIL;
    }
    return OK;
}
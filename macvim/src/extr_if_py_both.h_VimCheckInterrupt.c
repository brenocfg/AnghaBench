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
 int /*<<< orphan*/  PyErr_SetNone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_KeyboardInterrupt ; 
 scalar_t__ got_int ; 

__attribute__((used)) static int
VimCheckInterrupt(void)
{
    if (got_int)
    {
	PyErr_SetNone(PyExc_KeyboardInterrupt);
	return 1;
    }
    return 0;
}
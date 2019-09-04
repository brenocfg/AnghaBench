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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  NewNpyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/ * npyiter_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
npyiter_exit(NewNpyArrayIterObject *self, PyObject *args)
{
    /* even if called via exception handling, writeback any data */
    return npyiter_close(self);
}
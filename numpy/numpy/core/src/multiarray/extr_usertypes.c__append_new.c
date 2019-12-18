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
 int NPY_NOTYPE ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 scalar_t__ realloc (int*,int) ; 

__attribute__((used)) static int
_append_new(int **p_types, int insert)
{
    int n = 0;
    int *newtypes;
    int *types = *p_types;

    while (types[n] != NPY_NOTYPE) {
        n++;
    }
    newtypes = (int *)realloc(types, (n + 2)*sizeof(int));
    if (newtypes == NULL) {
        PyErr_NoMemory();
        return -1;
    }
    newtypes[n] = insert;
    newtypes[n + 1] = NPY_NOTYPE;

    /* Replace the passed-in pointer */
    *p_types = newtypes;
    return 0;
}
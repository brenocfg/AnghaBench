#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * v_string; } ;
struct TYPE_5__ {TYPE_1__ vval; } ;
typedef  TYPE_2__ typval_T ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/ * vim_strsave (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
set_string_copy(char_u *str, typval_T *tv)
{
    tv->vval.v_string = vim_strsave(str);
    if (tv->vval.v_string == NULL)
    {
	PyErr_NoMemory();
	return -1;
    }
    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  opt_type; int /*<<< orphan*/  lastoption; } ;
typedef  TYPE_1__ optiterinfo_T ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 int /*<<< orphan*/ * option_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
OptionsIterNext(optiterinfo_T **oii)
{
    char_u	*name;

    if ((name = option_iter_next(&((*oii)->lastoption), (*oii)->opt_type)))
	return PyString_FromString((char *)name);

    return NULL;
}
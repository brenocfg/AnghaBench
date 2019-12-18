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
typedef  int /*<<< orphan*/  Dragon4_Scratch ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  _bigint_static ; 
 int _bigint_static_in_use ; 

__attribute__((used)) static Dragon4_Scratch*
get_dragon4_bigint_scratch(void) {
    /* this test+set is not threadsafe, but no matter because we have GIL */
    if (_bigint_static_in_use) {
        PyErr_SetString(PyExc_RuntimeError,
            "numpy float printing code is not re-entrant. "
            "Ping the devs to fix it.");
        return NULL;
    }
    _bigint_static_in_use = 1;

    /* in this dummy implementation we only return the static allocation */
    return &_bigint_static;
}
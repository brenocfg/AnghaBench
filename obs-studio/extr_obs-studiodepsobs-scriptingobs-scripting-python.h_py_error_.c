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
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/  warn (char*,char const*,int) ; 

__attribute__((used)) static inline bool py_error_(const char *func, int line)
{
	if (PyErr_Occurred()) {
		warn("Python failure in %s:%d:", func, line);
		PyErr_Print();
		return true;
	}
	return false;
}
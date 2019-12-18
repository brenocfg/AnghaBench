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

/* Variables and functions */
 int /*<<< orphan*/  OBS_INVALID_HOTKEY_ID ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLongLong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline PyObject *py_invalid_hotkey_id()
{
	return PyLong_FromUnsignedLongLong(OBS_INVALID_HOTKEY_ID);
}
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
 int /*<<< orphan*/  PyGILState_Ensure () ; 
 int /*<<< orphan*/  Py_Finalize () ; 
 scalar_t__ Py_IsInitialized () ; 
 int /*<<< orphan*/  end_dynamic_python3 () ; 
 scalar_t__ hinstPy3 ; 

void
python3_end()
{
    static int recurse = 0;

    /* If a crash occurs while doing this, don't try again. */
    if (recurse != 0)
	return;

    ++recurse;

#ifdef DYNAMIC_PYTHON3
    if (hinstPy3)
#endif
    if (Py_IsInitialized())
    {
	// acquire lock before finalizing
	PyGILState_Ensure();

	Py_Finalize();
    }

#ifdef DYNAMIC_PYTHON3
    end_dynamic_python3();
#endif

    --recurse;
}
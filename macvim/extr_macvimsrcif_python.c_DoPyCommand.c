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
typedef  int /*<<< orphan*/  (* runner ) (char*,void*) ;
typedef  int /*<<< orphan*/  (* rangeinitializer ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PythonIO_Flush () ; 
 scalar_t__ Python_Init () ; 
 int /*<<< orphan*/  Python_Lock_Vim () ; 
 int /*<<< orphan*/  Python_Release_Vim () ; 
 int /*<<< orphan*/  Python_RestoreThread () ; 
 int /*<<< orphan*/  Python_SaveThread () ; 
 int /*<<< orphan*/  _ (char*) ; 

__attribute__((used)) static void
DoPyCommand(const char *cmd, rangeinitializer init_range, runner run, void *arg)
{
#ifndef PY_CAN_RECURSE
    static int		recursive = 0;
#endif
#if defined(MACOS) && !defined(MACOS_X_UNIX)
    GrafPtr		oldPort;
#endif
#if defined(HAVE_LOCALE_H) || defined(X_LOCALE)
    char		*saved_locale;
#endif
#ifdef PY_CAN_RECURSE
    PyGILState_STATE	pygilstate;
#endif

#ifndef PY_CAN_RECURSE
    if (recursive)
    {
	EMSG(_("E659: Cannot invoke Python recursively"));
	return;
    }
    ++recursive;
#endif

#if defined(MACOS) && !defined(MACOS_X_UNIX)
    GetPort(&oldPort);
    /* Check if the Python library is available */
    if ((Ptr)PyMac_Initialize == (Ptr)kUnresolvedCFragSymbolAddress)
	goto theend;
#endif
    if (Python_Init())
	goto theend;

    init_range(arg);

    Python_Release_Vim();	    /* leave vim */

#if defined(HAVE_LOCALE_H) || defined(X_LOCALE)
    /* Python only works properly when the LC_NUMERIC locale is "C". */
    saved_locale = setlocale(LC_NUMERIC, NULL);
    if (saved_locale == NULL || STRCMP(saved_locale, "C") == 0)
	saved_locale = NULL;
    else
    {
	/* Need to make a copy, value may change when setting new locale. */
	saved_locale = (char *) PY_STRSAVE(saved_locale);
	(void)setlocale(LC_NUMERIC, "C");
    }
#endif

#ifdef PY_CAN_RECURSE
    pygilstate = PyGILState_Ensure();
#else
    Python_RestoreThread();	    /* enter python */
#endif

    run((char *) cmd, arg
#ifdef PY_CAN_RECURSE
	    , &pygilstate
#endif
	    );

#ifdef PY_CAN_RECURSE
    PyGILState_Release(pygilstate);
#else
    Python_SaveThread();	    /* leave python */
#endif

#if defined(HAVE_LOCALE_H) || defined(X_LOCALE)
    if (saved_locale != NULL)
    {
	(void)setlocale(LC_NUMERIC, saved_locale);
	PyMem_Free(saved_locale);
    }
#endif

    Python_Lock_Vim();		    /* enter vim */
    PythonIO_Flush();
#if defined(MACOS) && !defined(MACOS_X_UNIX)
    SetPort(oldPort);
#endif

theend:
#ifndef PY_CAN_RECURSE
    --recursive;
#endif
    return;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* setlocal; } ;
struct TYPE_5__ {int /*<<< orphan*/  Environment; void* DelayedExpansion; void* EnableExtensions; struct TYPE_5__* Prev; } ;
typedef  TYPE_1__ SETLOCAL ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  DuplicateEnvironment () ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* bDelayedExpansion ; 
 void* bEnableExtensions ; 
 TYPE_4__* bc ; 
 TYPE_1__* cmd_alloc (int) ; 
 int /*<<< orphan*/  cmd_free (TYPE_1__*) ; 
 int /*<<< orphan*/  error_invalid_parameter_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_out_of_memory () ; 
 int /*<<< orphan*/  freep (int /*<<< orphan*/ *) ; 
 int nErrorLevel ; 
 int /*<<< orphan*/ * splitspace (int /*<<< orphan*/ ,int*) ; 

INT cmd_setlocal(LPTSTR param)
{
    SETLOCAL *Saved;
    LPTSTR *arg;
    INT argc, i;

    /* SETLOCAL only works inside a batch file */
    if (!bc)
        return 0;

    Saved = cmd_alloc(sizeof(SETLOCAL));
    if (!Saved)
    {
        WARN("Cannot allocate memory for Saved!\n");
        error_out_of_memory();
        return 1;
    }
    Saved->Prev = bc->setlocal;
    Saved->EnableExtensions = bEnableExtensions;
    Saved->DelayedExpansion = bDelayedExpansion;
    Saved->Environment = DuplicateEnvironment();
    if (!Saved->Environment)
    {
        error_out_of_memory();
        cmd_free(Saved);
        return 1;
    }
    bc->setlocal = Saved;

    nErrorLevel = 0;

    arg = splitspace(param, &argc);
    for (i = 0; i < argc; i++)
    {
        if (!_tcsicmp(arg[i], _T("enableextensions")))
            /* FIXME: not implemented! */
            bEnableExtensions = TRUE;
        else if (!_tcsicmp(arg[i], _T("disableextensions")))
            /* FIXME: not implemented! */
            bEnableExtensions = FALSE;
        else if (!_tcsicmp(arg[i], _T("enabledelayedexpansion")))
            bDelayedExpansion = TRUE;
        else if (!_tcsicmp(arg[i], _T("disabledelayedexpansion")))
            bDelayedExpansion = FALSE;
        else
        {
            error_invalid_parameter_format(arg[i]);
            break;
        }
    }
    freep(arg);

    return nErrorLevel;
}
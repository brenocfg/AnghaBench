#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pltcl_proc_ptr ;
typedef  int /*<<< orphan*/  pltcl_proc_key ;
typedef  int /*<<< orphan*/  pltcl_interp_desc ;
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_6__ {int /*<<< orphan*/  serviceModeHookProc; int /*<<< orphan*/  alertNotifierProc; int /*<<< orphan*/  finalizeNotifierProc; int /*<<< orphan*/  initNotifierProc; int /*<<< orphan*/  deleteFileHandlerProc; int /*<<< orphan*/  createFileHandlerProc; int /*<<< orphan*/  waitForEventProc; int /*<<< orphan*/  setTimerProc; } ;
typedef  TYPE_1__ Tcl_NotifierProcs ;
struct TYPE_7__ {int keysize; int entrysize; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  DefineCustomStringVariable (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  PGC_SUSET ; 
 scalar_t__ TCL_ERROR ; 
 int /*<<< orphan*/  TEXTDOMAIN ; 
 int /*<<< orphan*/ * Tcl_CreateInterp () ; 
 int /*<<< orphan*/  Tcl_FindExecutable (char*) ; 
 scalar_t__ Tcl_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_SetNotifier (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 void* hash_create (char*,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_bindtextdomain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pltcl_AlertNotifier ; 
 int /*<<< orphan*/  pltcl_CreateFileHandler ; 
 int /*<<< orphan*/  pltcl_DeleteFileHandler ; 
 int /*<<< orphan*/  pltcl_FinalizeNotifier ; 
 int /*<<< orphan*/  pltcl_InitNotifier ; 
 int /*<<< orphan*/  pltcl_ServiceModeHook ; 
 int /*<<< orphan*/  pltcl_SetTimer ; 
 int /*<<< orphan*/  pltcl_WaitForEvent ; 
 int /*<<< orphan*/ * pltcl_hold_interp ; 
 void* pltcl_interp_htab ; 
 int pltcl_pm_init_done ; 
 void* pltcl_proc_htab ; 
 int /*<<< orphan*/  pltcl_start_proc ; 
 int /*<<< orphan*/  pltclu_start_proc ; 

void
_PG_init(void)
{
	Tcl_NotifierProcs notifier;
	HASHCTL		hash_ctl;

	/* Be sure we do initialization only once (should be redundant now) */
	if (pltcl_pm_init_done)
		return;

	pg_bindtextdomain(TEXTDOMAIN);

#ifdef WIN32
	/* Required on win32 to prevent error loading init.tcl */
	Tcl_FindExecutable("");
#endif

	/*
	 * Override the functions in the Notifier subsystem.  See comments above.
	 */
	notifier.setTimerProc = pltcl_SetTimer;
	notifier.waitForEventProc = pltcl_WaitForEvent;
	notifier.createFileHandlerProc = pltcl_CreateFileHandler;
	notifier.deleteFileHandlerProc = pltcl_DeleteFileHandler;
	notifier.initNotifierProc = pltcl_InitNotifier;
	notifier.finalizeNotifierProc = pltcl_FinalizeNotifier;
	notifier.alertNotifierProc = pltcl_AlertNotifier;
	notifier.serviceModeHookProc = pltcl_ServiceModeHook;
	Tcl_SetNotifier(&notifier);

	/************************************************************
	 * Create the dummy hold interpreter to prevent close of
	 * stdout and stderr on DeleteInterp
	 ************************************************************/
	if ((pltcl_hold_interp = Tcl_CreateInterp()) == NULL)
		elog(ERROR, "could not create master Tcl interpreter");
	if (Tcl_Init(pltcl_hold_interp) == TCL_ERROR)
		elog(ERROR, "could not initialize master Tcl interpreter");

	/************************************************************
	 * Create the hash table for working interpreters
	 ************************************************************/
	memset(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(Oid);
	hash_ctl.entrysize = sizeof(pltcl_interp_desc);
	pltcl_interp_htab = hash_create("PL/Tcl interpreters",
									8,
									&hash_ctl,
									HASH_ELEM | HASH_BLOBS);

	/************************************************************
	 * Create the hash table for function lookup
	 ************************************************************/
	memset(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(pltcl_proc_key);
	hash_ctl.entrysize = sizeof(pltcl_proc_ptr);
	pltcl_proc_htab = hash_create("PL/Tcl functions",
								  100,
								  &hash_ctl,
								  HASH_ELEM | HASH_BLOBS);

	/************************************************************
	 * Define PL/Tcl's custom GUCs
	 ************************************************************/
	DefineCustomStringVariable("pltcl.start_proc",
							   gettext_noop("PL/Tcl function to call once when pltcl is first used."),
							   NULL,
							   &pltcl_start_proc,
							   NULL,
							   PGC_SUSET, 0,
							   NULL, NULL, NULL);
	DefineCustomStringVariable("pltclu.start_proc",
							   gettext_noop("PL/TclU function to call once when pltclu is first used."),
							   NULL,
							   &pltclu_start_proc,
							   NULL,
							   PGC_SUSET, 0,
							   NULL, NULL, NULL);

	pltcl_pm_init_done = true;
}
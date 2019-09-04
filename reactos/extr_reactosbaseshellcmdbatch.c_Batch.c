#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct _SETLOCAL {int dummy; } ;
typedef  int /*<<< orphan*/  fpname ;
struct TYPE_10__ {int* shiftlevel; TYPE_1__* current; int /*<<< orphan*/ * raw_params; int /*<<< orphan*/  params; scalar_t__ bEcho; scalar_t__ mempos; int /*<<< orphan*/ * BatchFilePath; struct _SETLOCAL* setlocal; int /*<<< orphan*/ * RedirList; void* memfree; int /*<<< orphan*/  memsize; scalar_t__ mem; struct TYPE_10__* prev; } ;
struct TYPE_9__ {scalar_t__ Type; int /*<<< orphan*/  Redirections; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ PARSED_COMMAND ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/ * LPFOR_CONTEXT ;
typedef  int INT ;
typedef  scalar_t__ HANDLE ;
typedef  void* BOOL ;
typedef  TYPE_2__ BATCH_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  AddBatchRedirection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BatchFile2Mem (scalar_t__) ; 
 int /*<<< orphan*/  BatchParams (scalar_t__*,scalar_t__*) ; 
 scalar_t__ C_QUIET ; 
 int /*<<< orphan*/  ClearBatch () ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ConErrResPuts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConOutChar (scalar_t__) ; 
 scalar_t__ CreateFile (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EchoCommand (TYPE_1__*) ; 
 int ExecuteCommand (TYPE_1__*) ; 
 int /*<<< orphan*/  ExitBatch () ; 
 void* FALSE ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_FLAG_SEQUENTIAL_SCAN ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FreeCommand (TYPE_1__*) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetFullPathName (scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 TYPE_1__* ParseCommand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintPrompt () ; 
 int /*<<< orphan*/  STRING_BATCH_ERROR ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 void* TRUE ; 
 scalar_t__ _T (char) ; 
 scalar_t__ _tcsicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bDisableBatchEcho ; 
 scalar_t__ bEcho ; 
 int /*<<< orphan*/  bExit ; 
 int /*<<< orphan*/  bIgnoreEcho ; 
 TYPE_2__* bc ; 
 int /*<<< orphan*/ * cmd_dup (scalar_t__*) ; 
 int /*<<< orphan*/  cmd_goto (scalar_t__*) ; 
 int /*<<< orphan*/  debugstr_aw (scalar_t__*) ; 
 int /*<<< orphan*/  error_out_of_memory () ; 
 int /*<<< orphan*/ * fc ; 
 int nErrorLevel ; 

INT Batch(LPTSTR fullname, LPTSTR firstword, LPTSTR param, PARSED_COMMAND *Cmd)
{
    BATCH_CONTEXT new;
    LPFOR_CONTEXT saved_fc;
    INT i;
    INT ret = 0;
    BOOL same_fn = FALSE;

    HANDLE hFile = 0;
    SetLastError(0);
    if (bc && bc->mem)
    {
        TCHAR fpname[MAX_PATH];
        GetFullPathName(fullname, sizeof(fpname) / sizeof(TCHAR), fpname, NULL);
        if (_tcsicmp(bc->BatchFilePath,fpname)==0)
            same_fn=TRUE;
    }
    TRACE ("Batch: (\'%s\', \'%s\', \'%s\')  same_fn = %d\n",
        debugstr_aw(fullname), debugstr_aw(firstword), debugstr_aw(param), same_fn);

    if (!same_fn)
    {
        hFile = CreateFile(fullname, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE, NULL,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL |
                           FILE_FLAG_SEQUENTIAL_SCAN, NULL);

        if (hFile == INVALID_HANDLE_VALUE)
        {
            ConErrResPuts(STRING_BATCH_ERROR);
            return 1;
        }
    }

    if (bc != NULL && Cmd == bc->current)
    {
        /* Then we are transferring to another batch */
        ClearBatch();
        AddBatchRedirection(&Cmd->Redirections);
    }
    else
    {
        struct _SETLOCAL *setlocal = NULL;

        if (Cmd == NULL)
        {
            /* This is a CALL. CALL will set errorlevel to our return value, so
             * in order to keep the value of errorlevel unchanged in the case
             * of calling an empty batch file, we must return that same value. */
            ret = nErrorLevel;
        }
        else if (bc)
        {
            /* If a batch file runs another batch file as part of a compound command
             * (e.g. "x.bat & somethingelse") then the first file gets terminated. */

            /* Get its SETLOCAL stack so it can be migrated to the new context */
            setlocal = bc->setlocal;
            bc->setlocal = NULL;
            ExitBatch();
        }

        /* Create a new context. This function will not
         * return until this context has been exited */
        new.prev = bc;
        /* copy some fields in the new structure if it is the same file */
        if (same_fn)
        {
            new.mem     = bc->mem;
            new.memsize = bc->memsize;
            new.mempos  = 0;
            new.memfree = FALSE;    /* don't free this, being used before this */
        }
        bc = &new;
        bc->RedirList = NULL;
        bc->setlocal = setlocal;
    }

    GetFullPathName(fullname, sizeof(bc->BatchFilePath) / sizeof(TCHAR), bc->BatchFilePath, NULL);
    /*  if a new batch file, load it into memory and close the file */
    if (!same_fn)
    {
        BatchFile2Mem(hFile);
        CloseHandle(hFile);
    }

    bc->mempos = 0;    /* goto begin of batch file */
    bc->bEcho = bEcho; /* Preserve echo across batch calls */
    for (i = 0; i < 10; i++)
        bc->shiftlevel[i] = i;

    bc->params = BatchParams (firstword, param);
    //
    // Allocate enough memory to hold the params and copy them over without modifications
    //
    bc->raw_params = cmd_dup(param);
    if (bc->raw_params == NULL)
    {
        error_out_of_memory();
        return 1;
    }

    /* Check if this is a "CALL :label" */
    if (*firstword == _T(':'))
        cmd_goto(firstword);

    /* If we are calling from inside a FOR, hide the FOR variables */
    saved_fc = fc;
    fc = NULL;

    /* If we have created a new context, don't return
     * until this batch file has completed. */
    while (bc == &new && !bExit)
    {
        Cmd = ParseCommand(NULL);
        if (!Cmd)
            continue;

        /* JPP 19980807 */
        /* Echo batch file line */
        if (bEcho && !bDisableBatchEcho && Cmd->Type != C_QUIET)
        {
            if (!bIgnoreEcho)
                ConOutChar(_T('\n'));
            PrintPrompt();
            EchoCommand(Cmd);
            ConOutChar(_T('\n'));
        }

        bc->current = Cmd;
        ret = ExecuteCommand(Cmd);
        FreeCommand(Cmd);
    }

    /* Always return the current errorlevel */
    ret = nErrorLevel;

    TRACE ("Batch: returns TRUE\n");

    fc = saved_fc;
    return ret;
}
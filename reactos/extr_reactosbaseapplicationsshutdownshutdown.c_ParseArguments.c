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
struct CommandLineOptions {int shutdown_delay; int* remote_system; int* message; void* force; void* shutdown; void* restart; void* logoff; void* show_gui; void* hibernate; void* document_reason; void* reason; void* abort; } ;
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_BAD_LENGTH ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 void* FALSE ; 
 int /*<<< orphan*/  IDS_ERROR_MAX_COMMENT_LENGTH ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 void* ParseReasonCode (int*) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 void* TRUE ; 
 int _wtoi (int*) ; 
 int towlower (int) ; 
 int wcslen (int*) ; 

__attribute__((used)) static DWORD
ParseArguments(struct CommandLineOptions* pOpts, int argc, WCHAR *argv[])
{
    int index;

    if (!pOpts)
        return ERROR_INVALID_PARAMETER;

    /* Reset all flags in struct */
    pOpts->abort = FALSE;
    pOpts->force = FALSE;
    pOpts->logoff = FALSE;
    pOpts->restart = FALSE;
    pOpts->shutdown = FALSE;
    pOpts->document_reason = FALSE;
    pOpts->hibernate = FALSE;
    pOpts->shutdown_delay = 30;
    pOpts->remote_system = NULL;
    pOpts->reason = ParseReasonCode(NULL); /* NOTE: NEVER use 0 here since it can delay the shutdown. */
    pOpts->message = NULL;
    pOpts->show_gui = FALSE;

    /*
     * Determine which flags the user has specified
     * to the program so we can use them later.
     */
    for (index = 1; index < argc; index++)
    {
        if (argv[index][0] == L'-' || argv[index][0] == L'/')
        {
            switch (towlower(argv[index][1]))
            {
                case L'?': /* Help */
                    ConResPuts(StdOut, IDS_USAGE);
                    return ERROR_SUCCESS;

                case L'a': /* Cancel delayed shutdown */
                    pOpts->abort = TRUE;
                    break;

                case L'c': /* Comment on reason for shutdown */
                    if (index+1 >= argc)
                        return ERROR_INVALID_DATA;
                    if (!argv[index+1] || wcslen(argv[index+1]) <= 512)
                    {
                        pOpts->message = argv[index+1];
                        index++;
                    }
                    else
                    {
                        ConResPuts(StdErr, IDS_ERROR_MAX_COMMENT_LENGTH);
                        return ERROR_BAD_LENGTH;
                    }
                    break;

                case L'd': /* Reason code [p|u:]xx:yy */
                    if (index+1 >= argc)
                        return ERROR_INVALID_DATA;
                    pOpts->reason = ParseReasonCode(argv[index+1]);
                    index++;
                    break;

                case L'e': /* Documents reason for shutdown */
                    /* TODO: Determine what this flag does exactly. */
                    pOpts->document_reason = TRUE;
                    break;

                case L'f': /* Force shutdown without warning */
                    pOpts->force = TRUE;
                    break;

                case L'h': /* Hibernate the local computer */
                    pOpts->hibernate = TRUE;
                    break;

                case L'i': /* Shows GUI version of the tool */
                    pOpts->show_gui = TRUE;
                    break;

                case L'l': /* Logoff the current user */
                    pOpts->logoff = TRUE;
                    break;

                case L'm': /* Target remote systems (UNC name/IP address) */
                    if (index+1 >= argc)
                        return ERROR_INVALID_DATA;
                    pOpts->remote_system = argv[index+1];
                    index++;
                    break;

                case L'p': /* Turn off local computer with no warning/time-out */
                    pOpts->force = TRUE;
                    pOpts->shutdown_delay = 0;
                    break;

                case L'r': /* Restart computer */
                    pOpts->restart = TRUE;
                    break;

                case L's': /* Shutdown */
                    pOpts->shutdown = TRUE;
                    break;

                case L't': /* Shutdown delay */
                    if (index+1 >= argc)
                        return ERROR_INVALID_DATA;
                    pOpts->shutdown_delay = _wtoi(argv[index+1]);
                    if (pOpts->shutdown_delay > 0) 
                        pOpts->force = TRUE;
                    index++;
                    break;

                default:
                    /* Unknown arguments will exit the program. */
                    ConResPuts(StdOut, IDS_USAGE);
                    return ERROR_SUCCESS;
            }
        }
    }

    return ERROR_SUCCESS;
}
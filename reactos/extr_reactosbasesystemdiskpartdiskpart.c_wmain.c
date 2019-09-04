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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char* const) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreatePartitionList () ; 
 int /*<<< orphan*/  DestroyPartitionList () ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_APP_HEADER ; 
 int /*<<< orphan*/  IDS_APP_LEAVING ; 
 int /*<<< orphan*/  IDS_APP_USAGE ; 
 int /*<<< orphan*/  IDS_ERROR_MSG_BAD_ARG ; 
 int /*<<< orphan*/  IDS_ERROR_MSG_NO_SCRIPT ; 
 int /*<<< orphan*/  InterpretMain () ; 
 int /*<<< orphan*/  K32LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RunScript (char*) ; 
 int /*<<< orphan*/  SetConsoleTitleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowHeader () ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ _wcsicmp (char*,char*) ; 
 int _wtoi (char* const) ; 

int wmain(int argc, const LPWSTR argv[])
{
    LPCWSTR script = NULL;
    LPCWSTR tmpBuffer = NULL;
    WCHAR appTitle[50];
    int index, timeout;
    int result = EXIT_SUCCESS;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    /* Sets the title of the program so the user will have an easier time
    determining the current program, especially if diskpart is running a
    script */
    K32LoadStringW(GetModuleHandle(NULL), IDS_APP_HEADER, appTitle, ARRAYSIZE(appTitle));
    SetConsoleTitleW(appTitle);

    /* Sets the timeout value to 0 just in case the user doesn't
    specify a value */
    timeout = 0;

    CreatePartitionList();

    /* If there are no command arguments, then go straight to the interpreter */
    if (argc < 2)
    {
        ShowHeader();
        InterpretMain();
    }
    /* If there are command arguments, then process them */
    else
    {
        for (index = 1; index < argc; index++)
        {
            /* checks for flags */
            if ((argv[index][0] == '/')||
                (argv[index][0] == '-'))
            {
                tmpBuffer = argv[index] + 1;
            }
            else
            {
                /* If there is no flag, then return an error */
                ConResPrintf(StdErr, IDS_ERROR_MSG_BAD_ARG, argv[index]);
                result = EXIT_FAILURE;
                goto done;
            }

            /* Checks for the /? flag first since the program
            exits as soon as the usage list is shown. */
            if (_wcsicmp(tmpBuffer, L"?") == 0)
            {
                ConResPuts(StdOut, IDS_APP_USAGE);
                result = EXIT_SUCCESS;
                goto done;
            }
            /* Checks for the script flag */
            else if (_wcsicmp(tmpBuffer, L"s") == 0)
            {
                if ((index + 1) < argc)
                {
                    index++;
                    script = argv[index];
                }
            }
            /* Checks for the timeout flag */
            else if (_wcsicmp(tmpBuffer, L"t") == 0)
            {
                if ((index + 1) < argc)
                {
                    index++;
                    timeout = _wtoi(argv[index]);

                    /* If the number is a negative number, then
                    change it so that the time is executed properly. */
                    if (timeout < 0)
                        timeout = 0;
                }
            }
            else
            {
                /* Assume that the flag doesn't exist. */
                ConResPrintf(StdErr, IDS_ERROR_MSG_BAD_ARG, tmpBuffer);
                result = EXIT_FAILURE;
                goto done;
            }
        }

        /* Shows the program information */
        ShowHeader();

        /* Now we process the filename if it exists */
        if (script != NULL)
        {
            /* if the timeout is greater than 0, then assume
            that the user specified a specific time. */
            if (timeout > 0)
                Sleep(timeout * 1000);

            if (RunScript(script) == FALSE)
            {
                result = EXIT_FAILURE;
                goto done;
            }
        }
        else
        {
            /* Exit failure since the user wanted to run a script */
            ConResPrintf(StdErr, IDS_ERROR_MSG_NO_SCRIPT, script);
            result = EXIT_FAILURE;
            goto done;
        }
    }

    /* Let the user know the program is exiting */
    ConResPuts(StdOut, IDS_APP_LEAVING);

done:
    DestroyPartitionList();

    return result;
}
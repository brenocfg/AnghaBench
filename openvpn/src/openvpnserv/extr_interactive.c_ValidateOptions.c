#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  ovpn_admin_group; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CheckOption (char const*,int,char**,TYPE_1__*) ; 
 char** CommandLineToArgvW (char const*,int*) ; 
 int /*<<< orphan*/  ERROR_STARTUP_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IsOption (char*) ; 
 int /*<<< orphan*/  LocalFree (char**) ; 
 int /*<<< orphan*/  ReturnError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReturnLastError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _countof (char*) ; 
 int /*<<< orphan*/  exit_event ; 
 int /*<<< orphan*/  openvpn_swprintf (char*,int /*<<< orphan*/ ,char const*,char*,char const*,...) ; 
 TYPE_1__ settings ; 
 scalar_t__ wcscmp (char*,char*) ; 

__attribute__((used)) static BOOL
ValidateOptions(HANDLE pipe, const WCHAR *workdir, const WCHAR *options)
{
    WCHAR **argv;
    int argc;
    WCHAR buf[256];
    BOOL ret = FALSE;
    int i;
    const WCHAR *msg1 = L"You have specified a config file location (%s relative to %s)"
                        L" that requires admin approval. This error may be avoided"
                        L" by adding your account to the \"%s\" group";

    const WCHAR *msg2 = L"You have specified an option (%s) that may be used"
                        L" only with admin approval. This error may be avoided"
                        L" by adding your account to the \"%s\" group";

    argv = CommandLineToArgvW(options, &argc);

    if (!argv)
    {
        ReturnLastError(pipe, L"CommandLineToArgvW");
        ReturnError(pipe, ERROR_STARTUP_DATA, L"Cannot validate options", 1, &exit_event);
        goto out;
    }

    /* Note: argv[0] is the first option */
    if (argc < 1)  /* no options */
    {
        ret = TRUE;
        goto out;
    }

    /*
     * If only one argument, it is the config file
     */
    if (argc == 1)
    {
        WCHAR *argv_tmp[2] = { L"--config", argv[0] };

        if (!CheckOption(workdir, 2, argv_tmp, &settings))
        {
            openvpn_swprintf(buf, _countof(buf), msg1, argv[0], workdir,
                             settings.ovpn_admin_group);
            ReturnError(pipe, ERROR_STARTUP_DATA, buf, 1, &exit_event);
        }
        goto out;
    }

    for (i = 0; i < argc; ++i)
    {
        if (!IsOption(argv[i]))
        {
            continue;
        }

        if (!CheckOption(workdir, argc-i, &argv[i], &settings))
        {
            if (wcscmp(L"--config", argv[i]) == 0 && argc-i > 1)
            {
                openvpn_swprintf(buf, _countof(buf), msg1, argv[i+1], workdir,
                                 settings.ovpn_admin_group);
                ReturnError(pipe, ERROR_STARTUP_DATA, buf, 1, &exit_event);
            }
            else
            {
                openvpn_swprintf(buf, _countof(buf), msg2, argv[i],
                                 settings.ovpn_admin_group);
                ReturnError(pipe, ERROR_STARTUP_DATA, buf, 1, &exit_event);
            }
            goto out;
        }
    }

    /* all options passed */
    ret = TRUE;

out:
    if (argv)
    {
        LocalFree(argv);
    }
    return ret;
}
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
typedef  int INT ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BlankArgument (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetArgument (char*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDS_ERROR_1TIMES ; 
 int /*<<< orphan*/  IDS_ERROR_FQDN ; 
 int /*<<< orphan*/  IDS_ERROR_INVALIDARG ; 
 int /*<<< orphan*/  IDS_ERROR_INVALIDSYNTAX ; 
 int /*<<< orphan*/  IDS_ERROR_NH_LIST ; 
 int /*<<< orphan*/  IDS_ERROR_UPN ; 
 int /*<<< orphan*/  IDS_ERROR_VALUENOTALLOWED ; 
 int /*<<< orphan*/  IDS_ERROR_VALUEXPECTED ; 
 int /*<<< orphan*/  IDS_HELP ; 
 int /*<<< orphan*/  NameFullyQualifiedDN ; 
 int /*<<< orphan*/  NameSamCompatible ; 
 int /*<<< orphan*/  NameUserPrincipal ; 
 scalar_t__ NoHeader ; 
 int NoHeaderArgCount ; 
 scalar_t__ PrintFormat ; 
 int PrintFormatArgCount ; 
 scalar_t__ TRUE ; 
 int WAM_GROUPS ; 
 int WAM_PRIV ; 
 int WAM_USER ; 
 int /*<<< orphan*/  WhoamiFree (char*) ; 
 char* WhoamiGetUser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhoamiGroups () ; 
 char* WhoamiLoadRcString (int /*<<< orphan*/ ) ; 
 int WhoamiLogonId () ; 
 int /*<<< orphan*/  WhoamiPriv () ; 
 int /*<<< orphan*/  WhoamiUser () ; 
 scalar_t__ csv ; 
 scalar_t__ list ; 
 scalar_t__ table ; 
 scalar_t__ wcsicmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

int wmain(int argc, WCHAR* argv[])
{
    #define WAM_USER   1<<0
    #define WAM_GROUPS 1<<1
    #define WAM_PRIV   1<<2

    INT i;
    BYTE WamBit = 0;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();


    /* * * * * * * * * * * * * * * *
     * A: no parameters whatsoever */

    if (argc == 1)
    {
        /* if there's no arguments just choose the simple path and display the user's identity in lowercase */
        LPWSTR UserBuffer = WhoamiGetUser(NameSamCompatible);

        if (UserBuffer)
        {
            wprintf(L"%s\n", UserBuffer);
            WhoamiFree(UserBuffer);
            return 0;
        }
        else
        {
            return 1;
        }
    }

    /* first things first-- let's detect and manage both printing modifiers (/fo and /nh) */
    for (i = 1; i < argc; i++)
    {
        if (wcsicmp(argv[i], L"/nh") == 0)
        {
            NoHeaderArgCount++;

            if (NoHeader == FALSE)
            {
                NoHeader = TRUE;
                // wprintf(L"Headers disabled!\n");
                BlankArgument(i, argv);
            }
        }
    }

    for (i = 1; i < argc; i++)
    {
        if (wcsicmp(argv[i], L"/fo") == 0)
        {
            if ((i + 1) < argc)
            {
                // wprintf(L"exists another param after /fo\n");

                PrintFormatArgCount++;

                if (wcsicmp(argv[i + 1], L"table") == 0 && PrintFormat != table)
                {
                    PrintFormat = table;
                    // wprintf(L"Changed to table format\n");
                    BlankArgument(i, argv);
                    BlankArgument(i + 1, argv);
                }
                else if (wcsicmp(argv[i + 1], L"list") == 0 && PrintFormat != list)
                {
                    PrintFormat = list;
                    // wprintf(L"Changed to list format\n");
                    BlankArgument(i, argv);
                    BlankArgument(i + 1, argv);

                    /* looks like you can't use the "/fo list /nh" options together
                       for some stupid reason */
                    if (PrintFormat == list && NoHeader != FALSE)
                    {
                        wprintf(WhoamiLoadRcString(IDS_ERROR_NH_LIST));
                        return 1;
                    }
                }
                else if (wcsicmp(argv[i + 1], L"csv") == 0 && PrintFormat != csv)
                {
                    PrintFormat = csv;
                    // wprintf(L"Changed to csv format\n");
                    BlankArgument(i, argv);
                    BlankArgument(i + 1, argv);
                }
                /* /nh or /fo after /fo isn't parsed as a value */
                else if (wcsicmp(argv[i + 1], L"/nh") == 0 || wcsicmp(argv[i + 1], L"/fo") == 0

                /* same goes for the other named options, not ideal, but works */
                         || wcsicmp(argv[i + 1], L"/priv") == 0
                         || wcsicmp(argv[i + 1], L"/groups") == 0
                         || wcsicmp(argv[i + 1], L"/user") == 0
                         || wcsicmp(argv[i + 1], L"/all") == 0
                         || wcsicmp(argv[i + 1], L"") == 0)
                {
                    goto FoValueExpected;
                }
                else
                {
                    wprintf(WhoamiLoadRcString(IDS_ERROR_VALUENOTALLOWED), argv[i + 1]);
                    return 1;
                }
            }
            else
            {
                FoValueExpected:

                wprintf(WhoamiLoadRcString(IDS_ERROR_VALUEXPECTED));
                return 1;
            }
        }
    }

    if (NoHeaderArgCount >= 2)
    {
        wprintf(WhoamiLoadRcString(IDS_ERROR_1TIMES), L"/nh");
        return 1;
    }
    /* special case when there's just a /nh as argument; it outputs nothing */
    else if (NoHeaderArgCount == 1 && argc == 2)
    {
        return 0;
    }

    if (PrintFormatArgCount >= 2)
    {
        wprintf(WhoamiLoadRcString(IDS_ERROR_1TIMES), L"/fo");
        return 1;
    }
    /* if there's just /fo <format>... call it invalid */
    else if (PrintFormatArgCount == 1 && argc == 3)
    {
        goto InvalidSyntax;
    }

    /* * * * * * * * * * * * * *
     * B: one single parameter */

    if (argc == 2)
    {
        /* now let's try to parse the triumvirate of simpler, single (1) arguments... plus help */
        if (wcsicmp(argv[1], L"/?") == 0)
        {
            wprintf(WhoamiLoadRcString(IDS_HELP));
            return 0;
        }

        else if (wcsicmp(argv[1], L"/upn") == 0)
        {
            LPWSTR UserBuffer = WhoamiGetUser(NameUserPrincipal);

            if (UserBuffer)
            {
                wprintf(L"%s\n", UserBuffer);
                WhoamiFree(UserBuffer);
                return 0;
            }
            else
            {
                wprintf(WhoamiLoadRcString(IDS_ERROR_UPN));
                return 1;
            }
        }

        else if (wcsicmp(argv[1], L"/fqdn") == 0)
        {
            LPWSTR UserBuffer = WhoamiGetUser(NameFullyQualifiedDN);

            if (UserBuffer)
            {
                wprintf(L"%s\n", UserBuffer);
                WhoamiFree(UserBuffer);
                return 0;
            }
            else
            {
                wprintf(WhoamiLoadRcString(IDS_ERROR_FQDN));
                return 1;
            }
        }

        else if (wcsicmp(argv[1], L"/logonid") == 0)
        {
            return WhoamiLogonId();
        }
    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * C: One main parameter with extra tasty modifiers to play with */

    /* sometimes is just easier to whitelist for lack of a better method */
    for (i=1; i<argc; i++)
    {
        if ((wcsicmp(argv[i], L"/user") != 0) &&
            (wcsicmp(argv[i], L"/groups") != 0) &&
            (wcsicmp(argv[i], L"/priv") != 0) &&
            (wcsicmp(argv[i], L"/all") != 0) &&
            (wcsicmp(argv[i], L"") != 0))
        {
            wprintf(WhoamiLoadRcString(IDS_ERROR_INVALIDARG), argv[i]);
            return 1;
        }
    }

    if (GetArgument(L"/user", argc, argv))
    {
        WamBit |= WAM_USER;
    }

    if (GetArgument(L"/groups", argc, argv))
    {
        WamBit |= WAM_GROUPS;
    }

    if (GetArgument(L"/priv", argc, argv))
    {
        WamBit |= WAM_PRIV;
    }

    if (GetArgument(L"/all", argc, argv))
    {
        /* one can't have it /all and any of the other options at the same time */
        if ((WamBit & (WAM_USER | WAM_GROUPS | WAM_PRIV)) == 0)
        {
            WamBit |= (WAM_USER | WAM_GROUPS | WAM_PRIV);
        }
        else
        {
            goto InvalidSyntax;
        }
    }

    if (WamBit & WAM_USER)
    {
        WhoamiUser();
    }
    if (WamBit & WAM_GROUPS)
    {
        WhoamiGroups();
    }
    if (WamBit & WAM_PRIV)
    {
        WhoamiPriv();
    }

    return 0;

InvalidSyntax:
    wprintf(WhoamiLoadRcString(IDS_ERROR_INVALIDSYNTAX));
    return 1;
}
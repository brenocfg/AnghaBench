#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* DefaultServerAddress; char* DefaultServer; char* type; char* Class; void* MSxfr; void* vc; void* search; void* recurse; void* defname; void* d2; void* debug; int /*<<< orphan*/  root; int /*<<< orphan*/  domain; } ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 char* ClassAny ; 
 char* ClassIN ; 
 void* FALSE ; 
 scalar_t__ IsValidIP (char*) ; 
 int /*<<< orphan*/  PerformInternalLookup (char*,char*) ; 
 int /*<<< orphan*/  PerformLookup (char*) ; 
 int /*<<< orphan*/  PrintState () ; 
 int /*<<< orphan*/  PrintUsage () ; 
 int /*<<< orphan*/  RtlZeroMemory (char*,int) ; 
 TYPE_1__ State ; 
 void* TRUE ; 
 char* TypeA ; 
 char* TypeAAAA ; 
 char* TypeAny ; 
 char* TypeBoth ; 
 char* TypeCNAME ; 
 char* TypeMX ; 
 char* TypeNS ; 
 char* TypePTR ; 
 char* TypeSOA ; 
 char* TypeSRV ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

BOOL ParseCommandLine( int argc, char* argv[] )
{
    int i;
    BOOL NoMoreOptions = FALSE;
    BOOL Interactive = FALSE;
    CHAR AddrToResolve[256];
    CHAR Server[256];

    RtlZeroMemory( AddrToResolve, 256 );
    RtlZeroMemory( Server, 256 );

    if( 2 == argc )
    {
        /* In the Windows nslookup, usage is only displayed if /? is the only
           option specified on the command line. */
        if( !strncmp( "/?", argv[1], 2 ) )
        {
            PrintUsage();
            return 0;
        }
    }

    if( argc > 1 )
    {
        for( i = 1; i < argc; i += 1 )
        {
            if( NoMoreOptions )
            {
                strncpy( Server, argv[i], 255 );

                /* Determine which one to resolve. This is based on whether the
                   DNS server provided was an IP or an FQDN. */
                if( IsValidIP( Server ) )
                {
                    strncpy( State.DefaultServerAddress, Server, 16 );

                    PerformInternalLookup( State.DefaultServerAddress,
                                           State.DefaultServer );
                }
                else
                {
                    strncpy( State.DefaultServer, Server, 255 );

                    PerformInternalLookup( State.DefaultServer,
                                           State.DefaultServerAddress );
                }

                if( Interactive ) return 1;

                PerformLookup( AddrToResolve );

                return 0;
            }
            else
            {
                if( !strncmp( "-all", argv[i], 4 ) )
                {
                    PrintState();
                }
                else if( !strncmp( "-type=", argv[i], 6 ) )
                {
                    if( !strncmp( TypeA, &argv[i][6], strlen( TypeA ) ) )
                    {
                        State.type = TypeA;
                    }
                    else if( !strncmp( TypeAAAA, &argv[i][6], strlen( TypeAAAA ) ) )
                    {
                        State.type = TypeAAAA;
                    }
                    else if( !strncmp( TypeBoth, &argv[i][6], strlen( TypeBoth ) ) )
                    {
                        State.type = TypeBoth;
                    }
                    else if( !strncmp( TypeAny, &argv[i][6], strlen( TypeAny ) ) )
                    {
                        State.type = TypeAny;
                    }
                    else if( !strncmp( TypeCNAME, &argv[i][6], strlen( TypeCNAME ) ) )
                    {
                        State.type = TypeCNAME;
                    }
                    else if( !strncmp( TypeMX, &argv[i][6], strlen( TypeMX ) ) )
                    {
                        State.type = TypeMX;
                    }
                    else if( !strncmp( TypeNS, &argv[i][6], strlen( TypeNS ) ) )
                    {
                        State.type = TypeNS;
                    }
                    else if( !strncmp( TypePTR, &argv[i][6], strlen( TypePTR ) ) )
                    {
                        State.type = TypePTR;
                    }
                    else if( !strncmp( TypeSOA, &argv[i][6], strlen( TypeSOA ) ) )
                    {
                        State.type = TypeSOA;
                    }
                    else if( !strncmp( TypeSRV, &argv[i][6], strlen( TypeSRV ) ) )
                    {
                        State.type = TypeSRV;
                    }
                    else
                    {
                        _tprintf( _T("unknown query type: %s"), &argv[i][6] );
                    }
                }
                else if( !strncmp( "-domain=", argv[i], 8 ) )
                {
                    strcpy( State.domain, &argv[i][8] );
                }
                else if( !strncmp( "-srchlist=", argv[i], 10 ) )
                {
                }
                else if( !strncmp( "-root=", argv[i], 6 ) )
                {
                    strcpy( State.root, &argv[i][6] );
                }
                else if( !strncmp( "-retry=", argv[i], 7 ) )
                {
                }
                else if( !strncmp( "-timeout=", argv[i], 9 ) )
                {
                }
                else if( !strncmp( "-querytype=", argv[i], 11 ) )
                {
                    if( !strncmp( TypeA, &argv[i][11], strlen( TypeA ) ) )
                    {
                        State.type = TypeA;
                    }
                    else if( !strncmp( TypeAAAA, &argv[i][11], strlen( TypeAAAA ) ) )
                    {
                        State.type = TypeAAAA;
                    }
                    else if( !strncmp( TypeBoth, &argv[i][11], strlen( TypeBoth ) ) )
                    {
                        State.type = TypeBoth;
                    }
                    else if( !strncmp( TypeAny, &argv[i][11], strlen( TypeAny ) ) )
                    {
                        State.type = TypeAny;
                    }
                    else if( !strncmp( TypeCNAME, &argv[i][11], strlen( TypeCNAME ) ) )
                    {
                        State.type = TypeCNAME;
                    }
                    else if( !strncmp( TypeMX, &argv[i][11], strlen( TypeMX ) ) )
                    {
                        State.type = TypeMX;
                    }
                    else if( !strncmp( TypeNS, &argv[i][11], strlen( TypeNS ) ) )
                    {
                        State.type = TypeNS;
                    }
                    else if( !strncmp( TypePTR, &argv[i][11], strlen( TypePTR ) ) )
                    {
                        State.type = TypePTR;
                    }
                    else if( !strncmp( TypeSOA, &argv[i][11], strlen( TypeSOA ) ) )
                    {
                        State.type = TypeSOA;
                    }
                    else if( !strncmp( TypeSRV, &argv[i][11], strlen( TypeSRV ) ) )
                    {
                        State.type = TypeSRV;
                    }
                    else
                    {
                        _tprintf( _T("unknown query type: %s"), &argv[i][6] );
                    }
                }
                else if( !strncmp( "-class=", argv[i], 7 ) )
                {
                    if( !strncmp( ClassIN, &argv[i][7], strlen( ClassIN ) ) )
                    {
                        State.Class = ClassIN;
                    }
                    else if( !strncmp( ClassAny, &argv[i][7], strlen( ClassAny ) ) )
                    {
                        State.Class = ClassAny;
                    }
                    else
                    {
                        _tprintf( _T("unknown query class: %s"), &argv[i][7] );
                    }
                }
                else if( !strncmp( "-ixfrver=", argv[i], 9 ) )
                {
                }
                else if( !strncmp( "-debug", argv[i], 6 ) )
                {
                    State.debug = TRUE;
                }
                else if( !strncmp( "-nodebug", argv[i], 8 ) )
                {
                    State.debug = FALSE;
                    State.d2 = FALSE;
                }
                else if( !strncmp( "-d2", argv[i], 3 ) )
                {
                    State.d2 = TRUE;
                    State.debug = TRUE;
                }
                else if( !strncmp( "-nod2", argv[i], 5 ) )
                {
                    if( State.debug ) _tprintf( _T("d2 mode disabled; still in debug mode\n") );

                    State.d2 = FALSE;
                }
                else if( !strncmp( "-defname", argv[i], 8 ) )
                {
                    State.defname = TRUE;
                }
                else if( !strncmp( "-noddefname", argv[i], 10 ) )
                {
                    State.defname = FALSE;
                }
                else if( !strncmp( "-recurse", argv[i], 8 ) )
                {
                    State.recurse = TRUE;
                }
                else if( !strncmp( "-norecurse", argv[i], 10 ) )
                {
                    State.recurse = FALSE;
                }
                else if( !strncmp( "-search", argv[i], 7 ) )
                {
                    State.search = TRUE;
                }
                else if( !strncmp( "-nosearch", argv[i], 9 ) )
                {
                    State.search = FALSE;
                }
                else if( !strncmp( "-vc", argv[i], 3 ) )
                {
                    State.vc = TRUE;
                }
                else if( !strncmp( "-novc", argv[i], 5 ) )
                {
                    State.vc = FALSE;
                }
                else if( !strncmp( "-msxfr", argv[i], 6 ) )
                {
                    State.MSxfr = TRUE;
                }
                else if( !strncmp( "-nomsxfr", argv[i], 8 ) )
                {
                    State.MSxfr = FALSE;
                }
                else if( !strncmp( "-", argv[i], 1 ) && (strlen( argv[i] ) == 1) )
                {
                    /* Since we received just the plain - switch, we are going
                       to be entering interactive mode. We also will not be
                       parsing any more options. */
                    NoMoreOptions = TRUE;
                    Interactive = TRUE;
                }
                else
                {
                    /* Grab the address to resolve. No more options accepted
                       past this point. */
                    strncpy( AddrToResolve, argv[i], 255 );
                    NoMoreOptions = TRUE;
                }
            }
        }

        if( NoMoreOptions && !Interactive )
        {
            /* Get the FQDN of the DNS server. */
            PerformInternalLookup( State.DefaultServerAddress,
                                   State.DefaultServer );

            PerformLookup( AddrToResolve );

            return 0;
        }
    }

    /* Get the FQDN of the DNS server. */
    PerformInternalLookup( State.DefaultServerAddress,
                           State.DefaultServer );

    return 1;
}
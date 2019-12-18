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
typedef  int USHORT ;
typedef  scalar_t__ ULONG ;
typedef  int UCHAR ;
typedef  int /*<<< orphan*/ * PUSHORT ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/ * PSHORT ;
typedef  int* PCHAR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ClassIDtoClassName (int) ; 
 scalar_t__ ExtractIP (int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ExtractName (int*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  OpcodeIDtoOpcodeName (int) ; 
 int /*<<< orphan*/  RCodeIDtoRCodeName (int) ; 
 int TYPE_A ; 
 int TYPE_NS ; 
 int TYPE_SOA ; 
 int /*<<< orphan*/  TypeIDtoTypeName (int) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

void PrintDebug( PCHAR pBuffer, DWORD BufferLength )
{
    USHORT ResponseID;
    UCHAR Header1, Header2;
    USHORT NumQuestions, NumAnswers, NumAuthority, NumAdditional;
    USHORT Type, Class;
    ULONG TTL;
    CHAR pName[255];
    int d = 0, i = 0, k = 0;

    ResponseID = ntohs( ((PUSHORT)&pBuffer[i])[0] );
    i += 2;

    Header1 = pBuffer[i];
    i += 1;

    Header2 = pBuffer[i];
    i += 1;

    NumQuestions = ntohs( ((PSHORT)&pBuffer[i])[0] );
    i += 2;

    NumAnswers = ntohs( ((PSHORT)&pBuffer[i])[0] );
    i += 2;

    NumAuthority = ntohs( ((PUSHORT)&pBuffer[i])[0] );
    i += 2;

    NumAdditional = ntohs( ((PUSHORT)&pBuffer[i])[0] );
    i += 2;

    _tprintf( _T("------------\n") );
    _tprintf( _T("Got answer (%d bytes):\n"), (int)BufferLength );
    _tprintf( _T("    HEADER:\n") );
    _tprintf( _T("        opcode = %s, id = %d, rcode = %s\n"),
                 OpcodeIDtoOpcodeName( (Header1 & 0x78) >> 3 ),
                 (int)ResponseID,
                 RCodeIDtoRCodeName( Header2 & 0x0F ) );

    _tprintf( _T("        header flags:  response") );
    if( Header1 & 0x01 ) _tprintf( _T(", want recursion") );
    if( Header2 & 0x80 ) _tprintf( _T(", recursion avail.") );
    _tprintf( _T("\n") );

    _tprintf( _T("        questions = %d,  answers = %d,  "
                 "authority records = %d,  additional = %d\n\n"),
                 (int)NumQuestions,
                 (int)NumAnswers,
                 (int)NumAuthority,
                 (int)NumAdditional );

    if( NumQuestions )
    {
        _tprintf( _T("    QUESTIONS:\n") );

        for( k = 0; k < NumQuestions; k += 1 )
        {
            i += ExtractName( pBuffer, pName, i, 0 );

            _tprintf( _T("        %s"), pName );

            Type = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            Class = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            _tprintf( _T(", type = %s, class = %s\n"),
                      TypeIDtoTypeName( Type ),
                      ClassIDtoClassName( Class ) );
        }
    }

    if( NumAnswers )
    {
        _tprintf( _T("    ANSWERS:\n") );

        for( k = 0; k < NumAnswers; k += 1 )
        {
            _tprintf( _T("    ->  ") );

            /* Print out the name. */
            i += ExtractName( pBuffer, pName, i, 0 );

            _tprintf( _T("%s\n"), pName );

            /* Print out the type, class and data length. */
            Type = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            Class = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            TTL = ntohl( ((PULONG)&pBuffer[i])[0] );
            i += 4;

            d = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            _tprintf( _T("        type = %s, class = %s, dlen = %d\n"),
                      TypeIDtoTypeName( Type ),
                      ClassIDtoClassName( Class ),
                      d );

            /* Print out the answer. */
            if( TYPE_A == Type )
            {
                i += ExtractIP( pBuffer, pName, i );

                _tprintf( _T("        internet address = %s\n"), pName );
            }
            else
            {
                i += ExtractName( pBuffer, pName, i, d );

                _tprintf( _T("        name = %s\n"), pName );
            }

            _tprintf( _T("        ttl = %d ()\n"), (int)TTL );
        }
    }

    if( NumAuthority )
    {
        _tprintf( _T("    AUTHORITY RECORDS:\n") );

        for( k = 0; k < NumAuthority; k += 1 )
        {
            /* Print out the zone name. */
            i += ExtractName( pBuffer, pName, i, 0 );

            _tprintf( _T("    ->  %s\n"), pName );

            /* Print out the type, class, data length and TTL. */
            Type = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            Class = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            TTL = ntohl( ((PULONG)&pBuffer[i])[0] );
            i += 4;

            d = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            _tprintf( _T("        type = %s, class = %s, dlen = %d\n"),
                      TypeIDtoTypeName( Type ),
                      ClassIDtoClassName( Class ),
                      d );

            /* TODO: There might be more types? */
            if( TYPE_NS == Type )
            {
                /* Print out the NS. */
                i += ExtractName( pBuffer, pName, i, d );

                _tprintf( _T("        nameserver = %s\n"), pName );

                _tprintf( _T("        ttl = %d ()\n"), (int)TTL );
            }
            else if( TYPE_SOA == Type )
            {
                _tprintf( _T("        ttl = %d ()\n"), (int)TTL );

                /* Print out the primary NS. */
                i += ExtractName( pBuffer, pName, i, 0 );

                _tprintf( _T("        primary name server = %s\n"), pName );

                /* Print out the responsible mailbox. */
                i += ExtractName( pBuffer, pName, i, 0 );

                _tprintf( _T("        responsible mail addr = %s\n"), pName );

                /* Print out the serial, refresh, retry, expire and default TTL. */
                _tprintf( _T("        serial = ()\n") );
                _tprintf( _T("        refresh = ()\n") );
                _tprintf( _T("        retry = ()\n") );
                _tprintf( _T("        expire = ()\n") );
                _tprintf( _T("        default TTL = ()\n") );
                i += 20;
            }
        }
    }

    if( NumAdditional )
    {
        _tprintf( _T("    ADDITIONAL:\n") );

        for( k = 0; k < NumAdditional; k += 1 )
        {
            /* Print the name. */
            i += ExtractName( pBuffer, pName, i, 0 );

            _tprintf( _T("    ->  %s\n"), pName );

            /* Print out the type, class, data length and TTL. */
            Type = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            Class = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            TTL = ntohl( ((PULONG)&pBuffer[i])[0] );
            i += 4;

            d = ntohs( ((PUSHORT)&pBuffer[i])[0] );
            i += 2;

            _tprintf( _T("        type = %s, class = %s, dlen = %d\n"),
                      TypeIDtoTypeName( Type ),
                      ClassIDtoClassName( Class ),
                      d );

            /* TODO: There might be more types? */
            if( TYPE_A == Type )
            {
                /* Print out the NS. */
                i += ExtractIP( pBuffer, pName, i );

                _tprintf( _T("        internet address = %s\n"), pName );

                _tprintf( _T("        ttl = %d ()\n"), (int)TTL );
            }
        }
    }

    _tprintf( _T("\n------------\n") );
}
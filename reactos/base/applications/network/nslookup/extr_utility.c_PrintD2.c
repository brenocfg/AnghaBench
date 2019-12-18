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
typedef  int UCHAR ;
typedef  int /*<<< orphan*/ * PUSHORT ;
typedef  int /*<<< orphan*/ * PSHORT ;
typedef  int* PCHAR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ClassIDtoClassName (int) ; 
 scalar_t__ ExtractName (int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpcodeIDtoOpcodeName (int) ; 
 int /*<<< orphan*/  RCodeIDtoRCodeName (int) ; 
 int /*<<< orphan*/  TypeIDtoTypeName (int) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

void PrintD2( PCHAR pBuffer, DWORD BufferLength )
{
    USHORT RequestID;
    UCHAR Header1, Header2;
    USHORT NumQuestions, NumAnswers, NumAuthority, NumAdditional;
    USHORT Type, Class;
    CHAR pName[255];
    int i = 0, k = 0;

    RequestID = ntohs( ((PUSHORT)&pBuffer[i])[0] );
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
    _tprintf( _T("SendRequest(), len %d\n"), (int)BufferLength );
    _tprintf( _T("    HEADER:\n") );
    _tprintf( _T("        opcode = %s, id = %d, rcode = %s\n"),
                 OpcodeIDtoOpcodeName( (Header1 & 0x78) >> 3 ),
                 (int)RequestID,
                 RCodeIDtoRCodeName( Header2 & 0x0F ) );

    _tprintf( _T("        header flags:  query") );
    if( Header1 & 0x01 ) _tprintf( _T(", want recursion") );
    _tprintf( _T("\n") );

    _tprintf( _T("        questions = %d,  answers = %d,"
                 "  authority records = %d,  additional = %d\n\n"),
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

    _tprintf( _T("\n------------\n") );
}
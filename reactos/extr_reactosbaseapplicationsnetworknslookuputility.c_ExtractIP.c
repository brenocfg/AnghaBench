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
typedef  char* PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 

int ExtractIP( PCHAR pBuffer, PCHAR pOutput, USHORT Offset )
{
    int c = 0, l = 0, i = 0, v = 0;

    i = Offset;

    v = (UCHAR)pBuffer[i];
    l += 1;
    i += 1;

    sprintf( &pOutput[c], "%d.", v );
    c += strlen( &pOutput[c] );

    v = (UCHAR)pBuffer[i];
    l += 1;
    i += 1;

    sprintf( &pOutput[c], "%d.", v );
    c += strlen( &pOutput[c] );

    v = (UCHAR)pBuffer[i];
    l += 1;
    i += 1;

    sprintf( &pOutput[c], "%d.", v );
    c += strlen( &pOutput[c] );

    v = (UCHAR)pBuffer[i];
    l += 1;
    i += 1;

    sprintf( &pOutput[c], "%d", v );
    c += strlen( &pOutput[c] );

    pOutput[c] = '\0';

    return l;
}
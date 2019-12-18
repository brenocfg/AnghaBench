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
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int strlen (char*) ; 

BOOL IsValidIP( PCHAR pInput )
{
    int i = 0, l = 0, b = 0, c = 1;

    /* Max length of an IP, e.g. 255.255.255.255, is 15 characters. */
    l = strlen( pInput );
    if( l > 15 ) return FALSE;

    /* 'b' is the count of the current segment. It gets reset after seeing a
       '.'. */
    for( ; i < l; i += 1 )
    {
        if( '.' == pInput[i] )
        {
            if( !b ) return FALSE;
            if( b > 3 ) return FALSE;

            b = 0;
            c += 1;
        }
        else
        {
            b += 1;

            if( (pInput[i] < '0') || (pInput[i] > '9') ) return FALSE;
        }
    }

    if( b > 3 ) return FALSE;

    /* 'c' is the number of segments seen. If it's less than 4, then it's not
       a valid IP. */
    if( c < 4 ) return FALSE;

    return TRUE;
}
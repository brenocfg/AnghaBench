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

/* Variables and functions */
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void ReverseIP( PCHAR pIP, PCHAR pReturn )
{
    int i;
    int j;
    int k = 0;

    j = strlen( pIP ) - 1;
    i = j;

    /* We have A.B.C.D
       We will turn this into D.C.B.A and stick it in pReturn */

    /* A */
    for( ; i > 0; i -= 1 ) if( '.' == pIP[i] ) break;

    strncpy( &pReturn[k], &pIP[i + 1], (j - i) );
    k += (j - i);

    pReturn[k] = '.';
    k += 1;

    i -= 1;
    j = i;

    /* B */
    for( ; i > 0; i -= 1 ) if( '.' == pIP[i] ) break;

    strncpy( &pReturn[k], &pIP[i + 1], (j - i) );
    k += (j - i);

    pReturn[k] = '.';
    k += 1;

    i -= 1;
    j = i;

    /* C */
    for( ; i > 0; i -= 1 ) if( '.' == pIP[i] ) break;

    strncpy( &pReturn[k], &pIP[i + 1], (j - i) );
    k += (j - i);

    pReturn[k] = '.';
    k += 1;

    i -= 1;
    j = i;

    /* D */
    for( ; i > 0; i -= 1 );

    strncpy( &pReturn[k], &pIP[i], (j - i) + 1 );
    k += (j - i) + 1;

    pReturn[k] = '\0';
}
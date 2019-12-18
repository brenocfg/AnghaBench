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
typedef  unsigned int UINT ;
typedef  int* PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,...) ; 

void OskitDumpBuffer( PCHAR Data, UINT Len ) {
    unsigned int i;

    for( i = 0; i < Len; i++ ) {
        if( i && !(i & 0xf) ) DbgPrint( "\n" );
        if( !(i & 0xf) ) DbgPrint( "%p: ", (Data + i) );
        DbgPrint( " %02x", Data[i] & 0xff );
    }
    DbgPrint("\n");
}
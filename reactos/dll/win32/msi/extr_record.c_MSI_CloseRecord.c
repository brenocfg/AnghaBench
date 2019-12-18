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
typedef  size_t UINT ;
struct TYPE_2__ {size_t count; int /*<<< orphan*/ * fields; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIOBJECTHDR ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_FreeField (int /*<<< orphan*/ *) ; 

void MSI_CloseRecord( MSIOBJECTHDR *arg )
{
    MSIRECORD *rec = (MSIRECORD *) arg;
    UINT i;

    for( i=0; i<=rec->count; i++ )
        MSI_FreeField( &rec->fields[i] );
}
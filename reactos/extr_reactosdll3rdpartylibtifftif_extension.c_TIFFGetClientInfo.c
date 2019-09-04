#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* tif_clientinfo; } ;
struct TYPE_4__ {void* data; struct TYPE_4__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ TIFFClientInfoLink ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

void *TIFFGetClientInfo( TIFF *tif, const char *name )

{
    TIFFClientInfoLink *psLink = tif->tif_clientinfo;

    while( psLink != NULL && strcmp(psLink->name,name) != 0 )
        psLink = psLink->next;

    if( psLink != NULL )
        return psLink->data;
    else
        return NULL;
}
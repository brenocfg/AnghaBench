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
typedef  int tmsize_t ;
struct TYPE_5__ {TYPE_1__* tif_clientinfo; } ;
struct TYPE_4__ {char* name; void* data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ TIFFClientInfoLink ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ _TIFFmalloc (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void TIFFSetClientInfo( TIFF *tif, void *data, const char *name )

{
    TIFFClientInfoLink *psLink = tif->tif_clientinfo;

    /*
    ** Do we have an existing link with this name?  If so, just
    ** set it.
    */
    while( psLink != NULL && strcmp(psLink->name,name) != 0 )
        psLink = psLink->next;

    if( psLink != NULL )
    {
        psLink->data = data;
        return;
    }

    /*
    ** Create a new link.
    */

    psLink = (TIFFClientInfoLink *) _TIFFmalloc(sizeof(TIFFClientInfoLink));
    assert (psLink != NULL);
    psLink->next = tif->tif_clientinfo;
    psLink->name = (char *) _TIFFmalloc((tmsize_t)(strlen(name)+1));
    assert (psLink->name != NULL);
    strcpy(psLink->name, name);
    psLink->data = data;

    tif->tif_clientinfo = psLink;
}
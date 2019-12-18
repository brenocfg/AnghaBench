#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {TYPE_3__ IMoniker_iface; int /*<<< orphan*/ * name; int /*<<< orphan*/  has_class; scalar_t__ ref; } ;
typedef  TYPE_1__ MediaCatMoniker ;

/* Variables and functions */
 TYPE_1__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  DEVENUM_IMediaCatMoniker_AddRef (TYPE_3__*) ; 
 int /*<<< orphan*/  DEVENUM_LockModule () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IMoniker_Vtbl ; 

MediaCatMoniker * DEVENUM_IMediaCatMoniker_Construct(void)
{
    MediaCatMoniker * pMoniker = NULL;
    pMoniker = CoTaskMemAlloc(sizeof(MediaCatMoniker));
    if (!pMoniker)
        return NULL;

    pMoniker->IMoniker_iface.lpVtbl = &IMoniker_Vtbl;
    pMoniker->ref = 0;
    pMoniker->has_class = FALSE;
    pMoniker->name = NULL;

    DEVENUM_IMediaCatMoniker_AddRef(&pMoniker->IMoniker_iface);

    DEVENUM_LockModule();

    return pMoniker;
}
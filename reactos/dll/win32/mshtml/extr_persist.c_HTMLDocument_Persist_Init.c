#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {TYPE_5__ IPersistHistory_iface; TYPE_4__ IPersistStreamInit_iface; TYPE_3__ IMonikerProp_iface; TYPE_2__ IPersistFile_iface; TYPE_1__ IPersistMoniker_iface; } ;
typedef  TYPE_6__ HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  MonikerPropVtbl ; 
 int /*<<< orphan*/  PersistFileVtbl ; 
 int /*<<< orphan*/  PersistHistoryVtbl ; 
 int /*<<< orphan*/  PersistMonikerVtbl ; 
 int /*<<< orphan*/  PersistStreamInitVtbl ; 

void HTMLDocument_Persist_Init(HTMLDocument *This)
{
    This->IPersistMoniker_iface.lpVtbl = &PersistMonikerVtbl;
    This->IPersistFile_iface.lpVtbl = &PersistFileVtbl;
    This->IMonikerProp_iface.lpVtbl = &MonikerPropVtbl;
    This->IPersistStreamInit_iface.lpVtbl = &PersistStreamInitVtbl;
    This->IPersistHistory_iface.lpVtbl = &PersistHistoryVtbl;
}
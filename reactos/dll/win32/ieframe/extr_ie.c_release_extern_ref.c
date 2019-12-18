#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  doc_host; int /*<<< orphan*/  extern_ref; } ;
typedef  scalar_t__ LONG ;
typedef  TYPE_1__ InternetExplorer ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  deactivate_document (int /*<<< orphan*/ *) ; 

DWORD release_extern_ref(InternetExplorer *This, BOOL last_closes)
{
    LONG ref = InterlockedDecrement(&This->extern_ref);

    TRACE("ref = %d\n", ref);

    if(ref)
        return ref;

    if(!last_closes) {
        WARN("Last external connection released with FALSE last_closes.\n");
        return ref;
    }

    deactivate_document(&This->doc_host);
    return ref;
}
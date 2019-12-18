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
struct use_connection_context {TYPE_1__* resource; int /*<<< orphan*/ * result; int /*<<< orphan*/ * accessname; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/ * lpRemoteName; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_LOCALDRIVE ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void use_connection_set_accessnameW(struct use_connection_context *ctxt, WCHAR *local_name)
{
    WCHAR *accessname = ctxt->accessname;
    if (local_name)
    {
        lstrcpyW(accessname, local_name);
        if (ctxt->result)
            *ctxt->result = CONNECT_LOCALDRIVE;
    }
    else
        lstrcpyW(accessname, ctxt->resource->lpRemoteName);
}
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
struct use_connection_context {scalar_t__* buffer_size; int /*<<< orphan*/ * accessname; TYPE_1__* resource; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/ * lpRemoteName; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ lstrlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD use_connection_pre_set_accessnameW(struct use_connection_context *ctxt, WCHAR *local_name)
{
    if (ctxt->accessname && ctxt->buffer_size && *ctxt->buffer_size)
    {
        DWORD len;

        if (local_name)
            len = lstrlenW(local_name);
        else
            len = lstrlenW(ctxt->resource->lpRemoteName);

        if (++len > *ctxt->buffer_size)
        {
            *ctxt->buffer_size = len;
            return ERROR_MORE_DATA;
        }
    }
    else
        ctxt->accessname = NULL;

    return ERROR_SUCCESS;
}
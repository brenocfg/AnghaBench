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
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_2__ {scalar_t__ num_cols; } ;
typedef  TYPE_1__ MSISTREAMSVIEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAX_STREAM_NAME_LEN ; 
 scalar_t__ MSITYPE_NULLABLE ; 
 scalar_t__ MSITYPE_STRING ; 
 scalar_t__ MSITYPE_VALID ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szData ; 
 int /*<<< orphan*/  szName ; 
 int /*<<< orphan*/  szStreams ; 

__attribute__((used)) static UINT STREAMS_get_column_info( struct tagMSIVIEW *view, UINT n, LPCWSTR *name,
                                     UINT *type, BOOL *temporary, LPCWSTR *table_name )
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;

    TRACE("(%p, %d, %p, %p, %p, %p)\n", view, n, name, type, temporary, table_name);

    if (!n || n > sv->num_cols)
        return ERROR_INVALID_PARAMETER;

    switch (n)
    {
    case 1:
        if (name) *name = szName;
        if (type) *type = MSITYPE_STRING | MSITYPE_VALID | MAX_STREAM_NAME_LEN;
        break;

    case 2:
        if (name) *name = szData;
        if (type) *type = MSITYPE_STRING | MSITYPE_VALID | MSITYPE_NULLABLE;
        break;
    }
    if (table_name) *table_name = szStreams;
    if (temporary) *temporary = FALSE;
    return ERROR_SUCCESS;
}
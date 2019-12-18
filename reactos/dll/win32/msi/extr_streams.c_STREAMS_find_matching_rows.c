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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ num_cols; TYPE_2__* db; } ;
struct TYPE_5__ {scalar_t__ num_streams; TYPE_1__* streams; } ;
struct TYPE_4__ {scalar_t__ str_index; } ;
typedef  TYPE_3__ MSISTREAMSVIEW ;
typedef  int /*<<< orphan*/  MSIITERHANDLE ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ PtrToUlong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UlongToPtr (scalar_t__) ; 

__attribute__((used)) static UINT STREAMS_find_matching_rows(struct tagMSIVIEW *view, UINT col,
                                       UINT val, UINT *row, MSIITERHANDLE *handle)
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;
    UINT index = PtrToUlong(*handle);

    TRACE("(%p, %d, %d, %p, %p)\n", view, col, val, row, handle);

    if (!col || col > sv->num_cols)
        return ERROR_INVALID_PARAMETER;

    while (index < sv->db->num_streams)
    {
        if (sv->db->streams[index].str_index == val)
        {
            *row = index;
            break;
        }
        index++;
    }

    *handle = UlongToPtr(++index);

    if (index > sv->db->num_streams)
        return ERROR_NO_MORE_ITEMS;

    return ERROR_SUCCESS;
}
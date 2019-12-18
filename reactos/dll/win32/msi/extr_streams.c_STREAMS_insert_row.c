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
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ num_streams; int /*<<< orphan*/ * streams; } ;
struct TYPE_4__ {int num_cols; TYPE_2__* db; } ;
typedef  TYPE_1__ MSISTREAMSVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ STREAMS_set_row (struct tagMSIVIEW*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ streams_find_row (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streams_resize_table (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static UINT STREAMS_insert_row(struct tagMSIVIEW *view, MSIRECORD *rec, UINT row, BOOL temporary)
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;
    UINT i, r, num_rows = sv->db->num_streams + 1;

    TRACE("(%p, %p, %d, %d)\n", view, rec, row, temporary);

    r = streams_find_row( sv, rec, NULL );
    if (r == ERROR_SUCCESS)
        return ERROR_FUNCTION_FAILED;

    if (!streams_resize_table( sv->db, num_rows ))
        return ERROR_FUNCTION_FAILED;

    if (row == -1)
        row = num_rows - 1;

    /* shift the rows to make room for the new row */
    for (i = num_rows - 1; i > row; i--)
    {
        sv->db->streams[i] = sv->db->streams[i - 1];
    }

    r = STREAMS_set_row( view, row, rec, (1 << sv->num_cols) - 1 );
    if (r == ERROR_SUCCESS)
        sv->db->num_streams = num_rows;

    return r;
}
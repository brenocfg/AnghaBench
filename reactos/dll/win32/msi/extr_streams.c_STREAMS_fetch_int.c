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
typedef  int UINT ;
struct TYPE_6__ {TYPE_2__* db; } ;
struct TYPE_5__ {int num_streams; TYPE_1__* streams; } ;
struct TYPE_4__ {int str_index; } ;
typedef  TYPE_3__ MSISTREAMSVIEW ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int,int,int*) ; 

__attribute__((used)) static UINT STREAMS_fetch_int(struct tagMSIVIEW *view, UINT row, UINT col, UINT *val)
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;

    TRACE("(%p, %d, %d, %p)\n", view, row, col, val);

    if (col != 1)
        return ERROR_INVALID_PARAMETER;

    if (row >= sv->db->num_streams)
        return ERROR_NO_MORE_ITEMS;

    *val = sv->db->streams[row].str_index;

    return ERROR_SUCCESS;
}
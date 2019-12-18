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
struct TYPE_2__ {scalar_t__ num_rows; } ;
typedef  TYPE_1__ MSISTORAGESVIEW ;
typedef  int /*<<< orphan*/  IStream ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT STORAGES_fetch_stream(struct tagMSIVIEW *view, UINT row, UINT col, IStream **stm)
{
    MSISTORAGESVIEW *sv = (MSISTORAGESVIEW *)view;

    TRACE("(%p, %d, %d, %p)\n", view, row, col, stm);

    if (row >= sv->num_rows)
        return ERROR_FUNCTION_FAILED;

    return ERROR_INVALID_DATA;
}
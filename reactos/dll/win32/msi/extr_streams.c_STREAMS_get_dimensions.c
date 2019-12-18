#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {TYPE_1__* db; int /*<<< orphan*/  num_cols; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_streams; } ;
typedef  TYPE_2__ MSISTREAMSVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT STREAMS_get_dimensions(struct tagMSIVIEW *view, UINT *rows, UINT *cols)
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;

    TRACE("(%p, %p, %p)\n", view, rows, cols);

    if (cols) *cols = sv->num_cols;
    if (rows) *rows = sv->db->num_streams;

    return ERROR_SUCCESS;
}
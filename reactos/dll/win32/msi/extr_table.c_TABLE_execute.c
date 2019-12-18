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
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  num_cols; } ;
typedef  TYPE_1__ MSITABLEVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,...) ; 

__attribute__((used)) static UINT TABLE_execute( struct tagMSIVIEW *view, MSIRECORD *record )
{
    MSITABLEVIEW *tv = (MSITABLEVIEW*)view;

    TRACE("%p %p\n", tv, record);

    TRACE("There are %d columns\n", tv->num_cols );

    return ERROR_SUCCESS;
}
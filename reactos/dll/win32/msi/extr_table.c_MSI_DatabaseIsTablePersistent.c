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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  persistent; } ;
typedef  TYPE_1__ MSITABLE ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  MSICONDITION ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSICONDITION_ERROR ; 
 int /*<<< orphan*/  MSICONDITION_NONE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ get_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 

MSICONDITION MSI_DatabaseIsTablePersistent( MSIDATABASE *db, LPCWSTR table )
{
    MSITABLE *t;
    UINT r;

    TRACE("%p %s\n", db, debugstr_w(table));

    if (!table)
        return MSICONDITION_ERROR;

    r = get_table( db, table, &t );
    if (r != ERROR_SUCCESS)
        return MSICONDITION_NONE;

    return t->persistent;
}
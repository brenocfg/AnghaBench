#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  column; TYPE_3__* table; } ;
union ext_column {TYPE_1__ parsed; } ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_7__ {size_t table_index; TYPE_4__* view; } ;
struct TYPE_6__ {scalar_t__ (* fetch_int ) (TYPE_4__*,scalar_t__ const,int /*<<< orphan*/ ,scalar_t__*) ;} ;
typedef  TYPE_3__ JOINTABLE ;

/* Variables and functions */
 scalar_t__ ERROR_CONTINUE ; 
 scalar_t__ const INVALID_ROW_INDEX ; 
 scalar_t__ stub1 (TYPE_4__*,scalar_t__ const,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static inline UINT expr_fetch_value(const union ext_column *expr, const UINT rows[], UINT *val)
{
    JOINTABLE *table = expr->parsed.table;

    if( rows[table->table_index] == INVALID_ROW_INDEX )
    {
        *val = 1;
        return ERROR_CONTINUE;
    }
    return table->view->ops->fetch_int(table->view, rows[table->table_index],
                                        expr->parsed.column, val);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  table; int /*<<< orphan*/  column; } ;
struct TYPE_7__ {TYPE_1__ unparsed; } ;
struct TYPE_8__ {TYPE_2__ column; } ;
struct expr {TYPE_3__ u; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  table; int /*<<< orphan*/  column; } ;
typedef  TYPE_4__ column_info ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_COLUMN ; 
 struct expr* parser_alloc (void*,int) ; 

__attribute__((used)) static struct expr * EXPR_column( void *info, const column_info *column )
{
    struct expr *e = parser_alloc( info, sizeof *e );
    if( e )
    {
        e->type = EXPR_COLUMN;
        e->u.column.unparsed.column = column->column;
        e->u.column.unparsed.table = column->table;
    }
    return e;
}
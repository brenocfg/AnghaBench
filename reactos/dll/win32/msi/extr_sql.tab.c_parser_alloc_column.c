#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * next; scalar_t__ type; int /*<<< orphan*/ * val; void* column; void* table; } ;
typedef  TYPE_1__ column_info ;
typedef  void* LPCWSTR ;

/* Variables and functions */
 TYPE_1__* parser_alloc (void*,int) ; 

__attribute__((used)) static column_info *parser_alloc_column( void *info, LPCWSTR table, LPCWSTR column )
{
    column_info *col;

    col = parser_alloc( info, sizeof (*col) );
    if( col )
    {
        col->table = table;
        col->column = column;
        col->val = NULL;
        col->type = 0;
        col->next = NULL;
    }

    return col;
}
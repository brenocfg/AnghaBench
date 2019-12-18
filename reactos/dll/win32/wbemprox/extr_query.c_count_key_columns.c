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
struct view {TYPE_2__* table; } ;
typedef  size_t UINT ;
struct TYPE_4__ {size_t num_cols; TYPE_1__* columns; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int COL_FLAG_KEY ; 

__attribute__((used)) static UINT count_key_columns( const struct view *view )
{
    UINT i, num_keys = 0;

    for (i = 0; i < view->table->num_cols; i++)
    {
        if (view->table->columns[i].type & COL_FLAG_KEY) num_keys++;
    }
    return num_keys;
}
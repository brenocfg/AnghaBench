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
struct table {size_t num_cols; TYPE_1__* columns; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_2__ {int type; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int COL_FLAG_METHOD ; 
 int /*<<< orphan*/ * SysAllocString (int /*<<< orphan*/ ) ; 
 struct table* grab_table (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  release_table (struct table*) ; 

BSTR get_method_name( const WCHAR *class, UINT index )
{
    struct table *table;
    UINT i, count = 0;
    BSTR ret;

    if (!(table = grab_table( class ))) return NULL;

    for (i = 0; i < table->num_cols; i++)
    {
        if (table->columns[i].type & COL_FLAG_METHOD)
        {
            if (index == count)
            {
                ret = SysAllocString( table->columns[i].name );
                release_table( table );
                return ret;
            }
            count++;
        }
    }
    release_table( table );
    return NULL;
}
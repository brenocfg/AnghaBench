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
struct table {scalar_t__ num_rows; scalar_t__ num_cols; TYPE_1__* columns; } ;
typedef  int /*<<< orphan*/  class_method ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int type; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ LONGLONG ;
typedef  scalar_t__ INT_PTR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int COL_FLAG_METHOD ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WBEM_E_INVALID_METHOD ; 
 int /*<<< orphan*/  get_value (struct table const*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

HRESULT get_method( const struct table *table, const WCHAR *name, class_method **func )
{
    UINT i, j;

    for (i = 0; i < table->num_rows; i++)
    {
        for (j = 0; j < table->num_cols; j++)
        {
            if (table->columns[j].type & COL_FLAG_METHOD && !strcmpW( table->columns[j].name, name ))
            {
                HRESULT hr;
                LONGLONG val;

                if ((hr = get_value( table, i, j, &val )) != S_OK) return hr;
                *func = (class_method *)(INT_PTR)val;
                return S_OK;
            }
        }
    }
    return WBEM_E_INVALID_METHOD;

}
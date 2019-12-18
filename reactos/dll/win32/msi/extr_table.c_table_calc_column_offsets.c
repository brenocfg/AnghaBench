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
struct TYPE_4__ {int number; scalar_t__ offset; int /*<<< orphan*/  type; int /*<<< orphan*/  colname; } ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  TYPE_1__ MSICOLUMNINFO ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LONG_STR_BYTES ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bytes_per_column (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void table_calc_column_offsets( MSIDATABASE *db, MSICOLUMNINFO *colinfo, DWORD count )
{
    DWORD i;

    for (i = 0; colinfo && i < count; i++)
    {
         assert( i + 1 == colinfo[i].number );
         if (i) colinfo[i].offset = colinfo[i - 1].offset +
                                    bytes_per_column( db, &colinfo[i - 1], LONG_STR_BYTES );
         else colinfo[i].offset = 0;

         TRACE("column %d is [%s] with type %08x ofs %d\n",
               colinfo[i].number, debugstr_w(colinfo[i].colname),
               colinfo[i].type, colinfo[i].offset);
    }
}